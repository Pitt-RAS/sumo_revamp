#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H
#include <Arduino.h>
#include "config.h"
#include "depend/IMU_pipe.h"

class Accelerometer {
    private:
    	IMU_pipe& pipe;
    
        float max_forward_accel_ = 0;
		float max_radial_accel_ = 0;
		float xAccel = 0;
		float yAccel = 0; 
    public:
    	
  Accelerometer(): pipe(IMU_pipe::getInstance()){}

		void update();
		void resetMaxForwardAccel();
		void resetMaxRadialAccel();
		
		float getMaxForwardAccel();
		float getMaxRadialAccel();
		float getXAccel();
		float getYAccel();
};

#endif
