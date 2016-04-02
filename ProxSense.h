#ifndef PROXSENSE_H
#define PROXSENSE_H

class ProxSense
{
	bool prox[5];
	int proxPin[5];
	int weight[5];
	
public:
	void update();
	int generateAngle();
	bool sensorHigh();
 };
 
 #endif 
