#include "IMU_pipe.h"

volatile bool IMU_pipe::initialized_ = false;

void IMU_pipe::init() {
	// Initialize the I2C bus
	#ifdef CORE_TEENSY
		Wire.begin(I2C_MASTER, 0, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	#else
		Wire.begin();
		TWBR = 24; // Set I2C rate to 400k
	#endif

	// Initialize the MPU9150
	mpu_.initialize();

	/*LOG(mpu_.testConnection() ?
	  "MPU9150 connection successful\n" :
	  "MPU9150 connection failed\n");

	// Attach the interrupt vector
	LOG("Enabling MPU9150 interrupt detection...\n");*/
	pinMode(IMU_INTERRUPT_PIN, INPUT);

	#ifdef CORE_TEENSY
		uint8_t interrupt_pin = IMU_INTERRUPT_PIN;
	#else
		uint8_t interrupt_pin = digitalPinToInterrupt(IMU_INTERRUPT_PIN);
	#endif

	attachInterrupt(interrupt_pin,
				  []() -> void {
					if (IMU_pipe::initialized_) {
					  IMU_pipe::getInstance().interruptHandler();
					}
				  },
				  RISING);

	// Set gyro settings
	mpu_.setFullScaleGyroRange(MPU9150_GYRO_FS_2000); // range of 2000deg/s
	mpu_.setZGyroOffset(GYRO_OFFSET_SETTING);

	// Enable digital low pass filter with bandwidth of 188Hz
	mpu_.setDLPFMode(MPU9150_DLPF_BW_188);

	// Set sample rate of 500Hz (assuming DLPF is enabled)
	mpu_.setRate(1);

	// Set accelerometer settings
	mpu_.setFullScaleAccelRange(MPU9150_ACCEL_FS_16); // range of 16g
	mpu_.setZAccelOffset(1788);

	// Enable FIFO buffers
	mpu_.setFIFOEnabled(true);
	mpu_.setAccelFIFOEnabled(true);
	mpu_.setZGyroFIFOEnabled(true);

	// Enable interrupts
	mpu_.setIntFIFOBufferOverflowEnabled(true);
	mpu_.setIntDataReadyEnabled(true);

	// there's no good magnetometer interface in the MPU9150 library, so here it is

	#if 0
		// allow us to access the magnetometer over I2C
		I2Cdev::writeByte(MPU9150_DEFAULT_ADDRESS,
									  MPU9150_RA_INT_PIN_CFG,
									  0x02);
		delay(10);

		I2Cdev::writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01);
		delay(10);
		uint8_t mag_buf[4];
		I2Cdev::readBytes(MPU9150_RA_MAG_ADDRESS,
									  MPU9150_RA_MAG_XOUT_L,
									  4,
									  mag_buf);
		int16_t mx = (((int16_t)mag_buf[0]) << 8) | mag_buf[1];
		int16_t my = (((int16_t)mag_buf[2]) << 8) | mag_buf[3];
		last_mag_heading_ = atan2(mx, my) * RAD_TO_DEG;
		mag_heading_offset_ = -last_mag_heading_;
	#endif
}

void IMU_pipe::interruptHandler() {
  if (IMU_pipe::initialized_) {
    IMU_pipe& pipe = IMU_pipe::getInstance();
    pipe.mpu_interrupt_ = true;
    pipe.next_update_time_ = micros();
    if (pipe.handler_update_) {
      pipe.update();
    }
  }
}

IMU_pipe& IMU_pipe::getInstance() {
  static IMU_pipe inst;
  if (!initialized_) {
    inst.init();
    initialized_ = true;
  }

  return inst;
}

void IMU_pipe::calibrate() {
  //LOG("Calibrating gyro...\n");

  mpu_.setZGyroOffset(0);
  secondary_gyro_offset_ = 0;

  int16_t prev_offset = -1;
  int16_t offset = 0;
  uint32_t rounds = 0;

  // Keep adjusting the offset until the change we would make to the offset
  // is less than 1.  For some reason the gyro acts differently with different
  // offsets, which is why we can't do this in one shot.
  while (abs(offset - prev_offset) > 0) {
    uint32_t samples = 0;
    int32_t total = 0;

    // Variance * (samples - 1)
    // See https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
    float M2 = 0;

    // Take samples until the estimated std dev of the offset is below 0.5
    for (samples = 1; samples < 10 || M2 / sq(samples) > 0.25; samples++) {
      while (!update()) {
        // wait for actual data
      }

      if (samples > 10
          && abs(((float)total) / samples - last_gyro_reading_)
                > 2 * sqrt(M2 / samples)) {
        //LOG("Calibration failed, restarting calibration...\n");
        calibrate();
        return;
      }

      float delta = last_gyro_reading_ - ((float)total) / samples;
      total += last_gyro_reading_;
      float delta2 = last_gyro_reading_ - ((float)total) / (samples + 1);
      M2 += delta * delta2;
    }

    prev_offset = offset;
    rounds++;
    offset += total / samples;
    mpu_.setZGyroOffset(-offset);

   // LOG("Primary offset: %i\n", offset);
    //LOG("Samples: %lu\n", samples);
  }

 // LOG("Rounds: %li\n", rounds);

  // Calculate extra floating-point offset to add to integer offset stored
  // on the IMU itself.  This should be less than 1 if things are done
  // correctly
  uint32_t samples = 0;
  int32_t total = 0;
  float M2 = 0;

  for (samples = 1;
       samples < 10 || M2 / sq(samples) > sq(GYRO_CALIBRATION_TARGET_UNCERTAINTY);
       samples++) {
    while (!update()) {
      // wait for actual data
    }

    float delta = last_gyro_reading_ - (((float)total) / samples);
    total += last_gyro_reading_;
    float delta2 = last_gyro_reading_ - (((float)total) / (samples + 1));
    M2 += delta * delta2;
  }

  secondary_gyro_offset_ = ((float)total) / samples;
  //LOG("Secondary offset: %.10f\n", secondary_gyro_offset_);

  raw_heading_ = 0;
 // LOG("Gyro calibration successful\n");
}

bool IMU_pipe::update() {
	if (!mpu_interrupt_ && fifo_count_ < packet_size_) {
		return false;
	}

	uint8_t mpu_int_status;
	uint8_t fifo_buffer[64];
	float dt;
	uint16_t accel_x, accel_y;

	// reset interrupt flag and get INT_STATUS byte
	mpu_interrupt_ = false;
	mpu_int_status = mpu_.getIntStatus();

	// get current FIFO count
	fifo_count_ = mpu_.getFIFOCount();

	// check for FIFO overflow
	if ((mpu_int_status & 0x10) || fifo_count_ == 1024) {
		// reset so we can continue cleanly
		mpu_.resetFIFO();
		// LOG("FIFO overflow!\n");
		return false;

	// check for data ready interrupt
	} else if (mpu_int_status & 0x01) {
		// wait for correct available data length
		while (fifo_count_ < packet_size_) {
			fifo_count_ = mpu_.getFIFOCount();
		}

		// read a packet from FIFO
		mpu_.getFIFOBytes(fifo_buffer, packet_size_);

		// track FIFO count here in case there is > 1 packet available
		fifo_count_ -= packet_size_;

		// Accelerometer update
		accel_x = (uint16_t)fifo_buffer[0] << 8 | fifo_buffer[1];
		accel_y = (uint16_t)fifo_buffer[2] << 8 | fifo_buffer[3];
		
		accelX = accel_x/ACCEL_LSB_PER_G;
   		accelY = accel_y/ACCEL_LSB_PER_G;

		// Gyro update
		dt = (next_update_time_ - last_update_time_) / 1000000.0;
		raw_heading_ -= last_gyro_reading_ / GYRO_LSB_PER_DEG_PER_S * dt;

		if (abs(last_gyro_reading_) > FAILSAFE_GYRO_THRESHOLD)
		{
			over_gyro_threshold_ = true;
			angle_past_gyro_threshold_ -= last_gyro_reading_ / GYRO_LSB_PER_DEG_PER_S * dt;
			if (abs(angle_past_gyro_threshold_) > FAILSAFE_GYRO_ANGLE)
			{
				//freakOut("FUCK");
			}
		}
		else 
		{
			over_gyro_threshold_ = false;
			angle_past_gyro_threshold_ = 0;
		}
		
		last_gyro_reading_ = (uint16_t)fifo_buffer[6] << 8 | fifo_buffer[7];
		last_gyro_reading_ -= secondary_gyro_offset_;

		last_update_time_ = next_update_time_;

		return true;
	} 
	else
	{
		return false;
	}
}

void IMU_pipe::resetHeading() {
  raw_heading_ = 0;
  last_update_time_ = micros();
  mag_heading_offset_ = -last_mag_heading_;
}

void IMU_pipe::incrementHeading(float offset) {
  raw_heading_ += offset;
  mag_heading_offset_ -= offset;
  if (mag_heading_offset_ < -180) {
    mag_heading_offset_ += 360;
  } else if (mag_heading_offset_ > 180) {
    mag_heading_offset_ -= 360;
  }
}

float IMU_pipe::getHeading() {
  float elapsed_time = (micros() - last_update_time_) / 1000000.0;
  return raw_heading_ + last_gyro_reading_ * elapsed_time;
}




float IMU_pipe::getXAccel() {
  return accelX;
}
float IMU_pipe::getYAccel() {
  return accelY;
}

