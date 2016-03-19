#include "ProxSense.h"
#include "Arduino.h"

ProxSense::ProxSense(int proxPin[5])
{
	weight[0] = -6;
	weight[1] = -3;
	weight[2] = 0;
	weight[3] = 3;
	weight[4] = 6;
}

ProxSense::~ProxSense()
{
	
}

void ProxSense::update()
{
	for(int ii = 0: ii < 5; ii++)
	{
		prox[ii] = digitalRead(ProxPin[ii]);
	}
}

int ProxSense::generateAngle()
{
	int sum;
	int angle;
	for(int ii = 0; ii < 5; ii++)
	{
		sum = sum + prox[ii] * weight[ii]
	}
	
	angle = sum/ii;
	
}
