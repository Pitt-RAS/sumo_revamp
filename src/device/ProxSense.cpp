#include <Arduino.h>

#include "ProxSense.h"
#include "../config.h"

ProxSense::ProxSense(int proxPin[5], int weight[5])
{
	for (int pin_iter = 0; pin_iter < 5; pin_iter++){
		pinMode(prox_pin[pin_iter], INPUT);
	}
}

void ProxSense::update()
{
	for (int pin_iter = 0; pin_iter < 5; pin_iter++)
	{
        prox[pin_iter] = !digitalRead(proxPin[pin_iter]); // returns false if it sees something hence the !
	}
}

int ProxSense::generateAngle()
{
	int sum = 0;
	int angle;
	int num_active = 0;
	for (int pin_iter = 0; pin_iter < 5; pin_iter++)
	{
		if (prox[pin_iter]) { 
			num_active++;
			sum += weight[pin_iter];
		}
	}
	
	if (num_active > 0){
		angle = sum/num_active;
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
