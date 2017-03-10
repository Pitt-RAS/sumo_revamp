#include "Proximity.h"

ProxSense frontProx({F_PROX_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_P    IN},
              {-90,        -45,         0,           45,          90             });
ProxSense rearProx ({R_PROX_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_P    IN},                  
              {-90,        -45,         0,           45,          90             });

Proximity::Proximity(){
	
	frontProx.update();
	rearProx.update();
	
	update();
}


int Proximity::getFrontAngle()
{
	return front_angle;
}

int Proximity::getRearAngle()
{
	return rear_angle;
}

int Proximity::getDirection()
{
	return direction;
}

bool isInSight()
{
	return in_sight;
}


void Proximity::update()
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