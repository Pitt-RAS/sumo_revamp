#include <Arduino.h>
#include "Enemy.h"

int Enemy::getAngle()
{
	if (in_front)
	{
		return front_angle;
	}
	else
	{
		return rear_angle;
	}
}

void Enemy::update()
{
	front_angle = frontProx.readAngle();
	rear_angle  = rearProx.readAngle();
	
    if (front_angle != PROXIMITY_INACTIVE && rear_angle != PROXIMITY_INACTIVE) {
        // We see something on both sides so we will refer to our previous readingswhich entails doing nothing here, if we get more sophistcated we will detect which is closer to us and call that the true enemy direction
    }
    else if (front_angle != PROXIMITY_INACTIVE)
	{
        direction = 1;
		in_front = true;
		in_rear = false;
		in_sight = true;
	}
	else if (rear_angle != PROXIMITY_INACTIVE)
	{
        direction = -1;
		in_front = false;
		in_rear = true;
		in_sight = true;
	}
	else 
	{
        direction = 0;
		in_front = false;
		in_rear = false;
	    in_sight = false;
	}
	
}

