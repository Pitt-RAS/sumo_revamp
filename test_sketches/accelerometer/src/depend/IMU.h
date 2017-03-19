#ifndef IMU_H_
#define IMU_H_

#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU9150.h"
#include "../config.h"


class IMU {
  private:
    IMU() = default;
    void init();
    void interruptHandler();

    static volatile bool initialized_;

    volatile bool mpu_interrupt_ = false;

    MPU9150 mpu_;
    uint16_t packet_size_ = 8;
    uint16_t fifo_count_ = 0;

    float secondary_gyro_offset_ = GYRO_SECONDARY_OFFSET;

    float raw_heading_ = 0;
    int16_t last_gyro_reading_ = 0;
    unsigned long last_update_time_ = 0;
    volatile unsigned long next_update_time_ = 0;

    // true if we're currently over the gyro threshold
    bool over_gyro_threshold_ = false;

    // angle we've covered since we went over the threshold
    bool angle_past_gyro_threshold_ = 0;

    uint8_t updates_since_mag_reading_ = 0;

    // between -180 and 180
    float mag_heading_offset_;
    float last_mag_heading_;
    
    float accelX;
    float accelY;
    
    
  public:
    bool handler_update_ = true;

    // NEVER call this from an interrupt
    // (unless you're Orientation::interruptHandler, then it's kinda maybe ok)
    static IMU& getInstance();

    // determine the right offset for the gyro
    void calibrate();

    // get the latest data from the IMU
    bool update();

    // designates the current heading as 0 degrees
    void resetHeading();

    // shifts the current heading by the given offset
    // new heading = old heading + offset
    void incrementHeading(float offset);

    // Returns the current heading in degrees
    // Clockwise is positive
    // This does not wrap around, so it will continue increasing past 360
    //   or decreasing past -360
    float getHeading();

    float getXAccel();
    float getYAccel();
};

#endif
