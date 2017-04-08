#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H
#include <Arduino.h>
#include "config.h"
#include "depend/IMU.h"

class Accelerometer {
    private:
    	IMU& pipe;
    
        float max_forward_accel_ = 0;
		float max_radial_accel_ = 0;
		float xAccel = 0;
		float yAccel = 0; 
		
		 elapsedMicros elapsed_time;
		
		float x_accel_average = 0;
		float y_accel_average = 0;
		//uint16_t num_readings = 0;
		bool x_spike = false;
		bool y_spike = false;
		bool collide = false;
		
    public:
    	
  Accelerometer(): pipe(IMU::getInstance()){}

		void update();
		void resetMaxForwardAccel();
		void resetMaxRadialAccel();
		
		float getMaxForwardAccel();
		float getMaxRadialAccel();
		float getXAccel();
		float getYAccel();
		bool collision();
};

#endif
