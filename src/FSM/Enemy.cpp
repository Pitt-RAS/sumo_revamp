#include <Arduino.h>
#include "Enemy.h"

Enemy::Enemy()
{
	update();
}

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
	rear_angle = rearProx.readAngle();
	
	if (front_angle != PROXIMITY_INACTIVE)
	{
		in_front = true;
		in_rear = false;
		see_enemy = true;
	}
	else if (rear_angle != PROXIMITY_INACTIVE)
	{
		in_front = false;
		in_rear = true;
		see_enemy = true;
	}
	else 
	{
		in_front = false;
		in_rear = false;
		see_enemy = false;
	}
	
}

