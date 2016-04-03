#include "ProxSense.h"
#include "Arduino.h"

ProxSense::ProxSense(int proxPin_[5])
{
	weight[0] = -90;
	weight[1] = -45;
	weight[2] = 0;
	weight[3] = 45;
	weight[4] = 90;

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
