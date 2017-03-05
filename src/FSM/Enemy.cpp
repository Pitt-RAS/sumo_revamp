#include "Enemy.h"

//Create proximity sensor pin array initailize proximity sensors
int prox_front[5] = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int prox_front_weight[5] = {-90, -45, 0, 45, 90};
int prox_rear[5] = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int prox_rear_weight[5] = {-90, -45, 0, 45, 90};

frontProx(prox_front, prox_front_weight);
rearProx(proximity_rear, prox_rear_weight);

Enemy::Enemy()
{
	update();
}

int Enemy::getAngle()
{




	return angle_total;
}

void update()
{
	font_angle = frontProx.readAngle();
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





class Enemy
{
	private:
	
		float front_angle, rear_angle, angle_total;
		bool in_front, in_rear;
		
	public:
	
		bool see_enemy;
		
		Enemy();
		
		void update();
		float getAngle();
};

#endif

