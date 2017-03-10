#ifndef SUMO_PROX_H		
#define SUMO_PROX_H		
	
#include <Arduino.h>		
	
#include "../../config.h"		
#include "ProxSense.h"		
	
class Proximity		
{			
    private:

        int front_pin_array[5] = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
        int rear_pin_array[5]  = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
        int weight_array[5]    = {-90,         -45,         0,           45,          90         };

        ProxSense frontProx;
        ProxSense rearProx;

		bool in_sight;
        int enemy_direction;
		int front_angle;
        int rear_angle; 
        int enemy_angle;

	public:		
		Proximity() :
            frontProx(front_pin_array, weight_array),
            rearProx (rear_pin_array,  weight_array) {
                update();
            }       

		void update();	

		int getEnemyDirection();
		int getEnemyAngle();	
		bool enemyInSight();
};		
	
#endif
