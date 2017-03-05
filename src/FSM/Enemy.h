#ifndef SUMO_ENEMY_H_
#define SUMO_ENEMY_H_

#include <Arduino.h>

#include "../config.h"
#include "../device/ProxSense.h"

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
