#include "Accelerometer.h"

void Accelerometer::update()
{
	pipe.handler_update_ = false;
	while(!pipe.update()){}
	xAccel = pipe.getXAccel();
	yAccel = pipe.getYAccel();

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

bool Accelerometer::collision()
{
	/******NEEDS TUNING**********/
	
	float x_diff = 0;
	float y_diff = 0;

		x_accel_average = (float) (abs(x_accel_average) + abs(xAccel))/2;
		y_accel_average = (float) (abs(y_accel_average) + abs(yAccel))/2;
		
		x_diff = abs(abs(x_accel_average) - abs(xAccel));
		y_diff = abs(abs(y_accel_average) - abs(yAccel));
		
		if (x_diff > (.25 * abs(x_accel_average)))
		{
			x_spike = true;
		}
		else 
		{
			x_spike = false;
		}
		
		if (y_diff > (.25  * abs(y_accel_average)))
		{
			y_spike = true;
		}
		else 
		{
			y_spike = false;
		}
		
		if (x_spike && y_spike)
		{
			collide = true;
		}
		else 
		{
			collide = false;
		
		}
	return collide;
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
