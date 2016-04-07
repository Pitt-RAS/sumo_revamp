#include "ProxSense.h"
#include "Arduino.h"
#include "config.h"

ProxSense::ProxSense(int proxPin[5], int weight[5])
{
  memcpy(this->proxPin, proxPin, 5*sizeof(int));
  memcpy(this->weight, weight, 5*sizeof(int));
}

void ProxSense::update()
{
	for(int ii = 0; ii < 5; ii++)
	{
		prox[ii] = digitalRead(proxPin[ii]);
	}
}

int ProxSense::generateAngle()
{
	int sum = 0;
	int angle;
	int numActive = 0;
	for(int ii = 0; ii < 5; ii++)
	{
		if(prox[ii]){
			numActive++;
		}
		sum = sum + prox[ii] * weight[ii];
	}
	
	if(numActive > 0){
		angle = sum/numActive;
	}
	else {
		angle = PROXIMITY_INACTIVE; //Set to some error that we will never reach
	}

	return angle;
}

int ProxSense::readAngle() {
	update();
	return generateAngle();
}
