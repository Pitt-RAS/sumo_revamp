#ifndef MICROMOUSE_MOTION_H_
#define MICROMOUSE_MOTION_H_

#include "Arduino.h"
#include "config.h"
#include "encoding.h"
#include "motors.h"
#include "PIDController.h"

class Motion
{
private:
	Motor motor_l;
	Motor motor_r;
	
	PIDController pid_left;
	PIDController pid_right;

	//Private motion functions
	void setVelRaw(bool r, int pwmr, bool l, int pwml);

public:
  Motion();
  	void setVel(float v, float w);
	void setVel(float v);
	void charge();
	void search_arc();
	void deploy_ramps();
	
	//Must be called a set rate
	void update();

 };
 
#endif
