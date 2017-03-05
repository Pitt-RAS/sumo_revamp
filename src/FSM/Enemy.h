#ifndef SUMO_ENEMY_H_
#define SUMO_ENEMY_H_

#include <Arduino.h>

#include "../config.h"
#include "../device/motors.h"
#include "../device/ProxSense.h"
#include "../device/sensors_orientation.h"
#include "../device/LineSensor.h"

class Enemy
{
	private:
	
		int front_angle, rear_angle;
		
	public:
	
		bool see_enemy, in_front, in_rear;
		
		Enemy();
		
		void update();
		int getAngle();
};

#endif
