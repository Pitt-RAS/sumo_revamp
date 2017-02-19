#ifndef MICROMOUSE_MOTION_H_
#define MICROMOUSE_MOTION_H_

#include <Arduino.h>
#include <EncoderPittMicromouse.h>

#include "PIDController.h"

#include "../config.h"
#include "../device/motors.h"



class Motion
{
private:
	Motor motor_l;
	Motor motor_r;

	PIDController pid_left;
	PIDController pid_right;

	EncoderPittMicromouse flEn; //Front Left EncoderPittMicromouse (1)
	EncoderPittMicromouse frEn; //Front Right EncoderPittMicromouse (2)
	EncoderPittMicromouse blEn; //Back Left EncoderPittMicromouse (3)
	EncoderPittMicromouse brEn; //Back Right EncoderPittMicromouse (4)

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

	//Returns veloctiy of selected EncoderPittMicromouse
	float EnVelocityFL();
	float EnVelocityFR();
	float EnVelocityBL();
	float EnVelocityBR();

 };

#endif
