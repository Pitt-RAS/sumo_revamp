#include "Proximity.h"

void Proximity::update()
{
	front_angle = frontProx.readAngle();
	rear_angle  = rearProx.readAngle();
	
	/*if (front_angle != PROXIMITY_INACTIVE && rear_angle != PROXIMITY_INACTIVE) {
	// We see something on both sides so we will refer to our previous readingswhich entails doing nothing here, if we get more sophistcated we will detect which is closer to us and call that the true enemy direction
		if (enemy_direction == 1) {
			enemy_angle = front_angle;
		}
		else if (enemy_direction == -1) {
			enemy_angle = rear_angle;
		}
		else {
			enemy_angle = 0;
		}
		in_sight = true;
	}
	else*/ if (front_angle != PROXIMITY_INACTIVE)
	{
		enemy_direction = 1;
		enemy_angle = front_angle;
		in_sight = true;
	}
	/*else if (rear_angle != PROXIMITY_INACTIVE)
	{
		enemy_direction = -1;
		enemy_angle = rear_angle;
		in_sight = true;
	}*/
	else 
	{
		enemy_direction = 0;
		enemy_angle = 0; // out of safety, if set to proxinactive and we accidentally call a function with it, the angle would flip out
		in_sight = false;
	}
	 
}

int Proximity::getEnemyDirection() {
	return enemy_direction;
}

int Proximity::getEnemyAngle() {
    return enemy_angle;
}

bool Proximity::enemyInSight() {
	return in_sight;
}


