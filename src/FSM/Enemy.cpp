#include "Enemy.h"

//Create proximity sensor pin array initailize proximity sensors
int prox_front[5] = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int prox_front_weight[5] = {-90, -45, 0, 45, 90};
int prox_rear[5] = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int prox_rear_weight[5] = {-90, -45, 0, 45, 90};

ProxSense frontProx(prox_front, prox_front_weight);
ProxSense rearProx(prox_rear, prox_rear_weight);

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

