#ifndef MICROMOUSE_MOTION_H_
#define MICROMOUSE_MOTION_H_

#include "Arduino.h"
#include "config.h"
#include "motors.h"
#include "PIDController.h"
#include <EncoderPittMicromouse.h>

class Motion
{
private:
	Motor motor_l;
	Motor motor_r;
	
	PIDController pid_left;
	PIDController pid_right;
	
	EncoderPittMicromouse flEn; //Front Left Encoder (1)
	EncoderPittMicromouse frEn; //Front Right Encoder (2)
	EncoderPittMicromouse blEn; //Back Left Encoder (3)
	EncoderPittMicromouse brEn; //Back Right Encoder (4)

	float target_left_v, target_right_v;
	//Private motion functions
	void setVelRaw(bool r, int pwmr, bool l, int pwml);

public:
  Motion();
  	void setVelRaw(int pwmr, int pwml);

  	void setVel(float v, float w);
	void setVel(float v);
	void charge();
	void search_arc();
	void deploy_ramps();
	
	//Must be called a set rate
	void update();
	
	//Returns veloctiy of selected encoder
	float EnVelocityFL();
	float EnVelocityFR();
	float EnVelocityBL();
	float EnVelocityBR();

 };
 
#endif
