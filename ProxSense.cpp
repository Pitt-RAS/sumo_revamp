#include "ProxSense.h"
#include "Arduino.h"

ProxSense::ProxSense(int proxPin[5], int weight[5])
{
  memcpy(this->proxPin, proxPin, 5*sizeof(int));
  memcpy(this->weight, weight, 5*sizeof(int));

  for(int i = 0; i < 5; i++) {
    pinMode(proxPin[i], INPUT);
  }
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
	for(int ii = 0; ii < 5; ii++)
	{
		sum = sum + prox[ii] * weight[ii];
	}
	
	angle = sum/5;
	return angle;
}
