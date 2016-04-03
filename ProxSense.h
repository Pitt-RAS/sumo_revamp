#ifndef PROXSENSE_H
#define PROXSENSE_H

class ProxSense
{
private:
	bool prox[5];
	int proxPin[5];
	int weight[5];
	
public:
  ProxSense(int*, int*);
	void update();
	int generateAngle();
	bool sensorHigh();
 };
 
 #endif 
