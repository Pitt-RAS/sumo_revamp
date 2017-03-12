#include "Accelerometer.h"

void Accelerometer::update()
{
	while(!pipe.update()){}
	pipe.handler_update_ = false;
	xAccel = pipe.getXAccel();
	yAccel = pipe.getYAccel();
	
    xAccel /= ACCEL_LSB_PER_G;
    yAccel /= ACCEL_LSB_PER_G;

    if (abs(xAccel) > FAILSAFE_ACCEL_THRESHOLD || abs(yAccel) > FAILSAFE_ACCEL_THRESHOLD) 
    {
    	//shit hit the fan
    }

    if (abs(xAccel) > max_radial_accel_) 
    {
      max_radial_accel_ = xAccel;
    }

    if (abs(yAccel) > max_forward_accel_)
    {
      max_forward_accel_ = yAccel;
    }

}

void Accelerometer::resetMaxForwardAccel() {
  max_forward_accel_ = 0;
}

void Accelerometer::resetMaxRadialAccel() {
  max_radial_accel_ = 0;
}

float Accelerometer::getMaxForwardAccel() {
  return max_forward_accel_;
}

float Accelerometer::getMaxRadialAccel() {
  return max_radial_accel_;
}

float Accelerometer::getXAccel() {
  return xAccel;
}

float Accelerometer::getYAccel() {
  return yAccel;
}
