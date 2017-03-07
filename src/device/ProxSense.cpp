#include <Arduino.h>

#include "ProxSense.h"
#include "../config.h"

void ProxSense::update()
{
	for (int pin_iter = 0; pin_iter < 5; pin_iter++)
	{
        prox[pin_iter] = !digitalRead(pin_array[pin_iter]); // returns false if it sees something hence the !
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
			sum += weight_array[pin_iter];
		}
	}
	
	if (num_active > 0){
		angle = sum / num_active;
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
