#include <Arduino.h>

#include "ProxSense.h"
#include "config.h"

ProxSense::ProxSense(int proxPin[5], int weight[5])
{
	memcpy(this->proxPin, proxPin, 5*sizeof(int));
	memcpy(this->weight, weight, 5*sizeof(int));

	for (int i=0; i<5; i++){
		pinMode(proxPin[i], INPUT);
	}
}

void ProxSense::update()
{
	for(int ii = 0; ii < 5; ii++)
	{
		prox[ii] = digitalRead(proxPin[ii]);
    Serial.print(ii);
    Serial.println(prox[ii]);
	}
}

int ProxSense::generateAngle()
{
	int sum = 0;
	int angle;
	int numActive = 0;
	for(int ii = 0; ii < 5; ii++)
	{
		if(!prox[ii]){
			numActive++;
			sum += weight[ii];
		}
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
