#ifndef SUMO_PROX_H		
#define SUMO_PROX_H		
	
#include <Arduino.h>		
	
#include "../../config.h"		
#include "ProxSense.h"		
	
class Proximity		
{			
	public:		
		Proximity();	

		void update();	

		int getFrontAngle();	
		int getRearAngle();
		int getDirection();
		bool isInSight();

		int front_angle, rear_angle; 
		int direction; // 1 or 1		

		bool in_sight, in_front, in_rear;
};		
	
#endif