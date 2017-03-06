#ifndef SUMO_ENEMY_H
#define SUMO_ENEMY_H

#include <Arduino.h>

#include "../config.h"
#include "../device/ProxSense.h"

class Enemy
{
	private:
	
		int front_angle, rear_angle;
        ProxSense& frontProx, rearProx;
		
	public:
        Enemy(ProxSense& frontProxInput, ProxSense& rearProxInput) : 
            frontProx(frontProxInput), rearProx(rearProxInput) {}
    
        bool see_enemy, in_front, in_rear;
        int direction; // 1 or -1
        
        void update();
        int getAngle();
        int getDirection();
};

#endif
