#ifndef MICROMOUSE_MOTION_H_
#define MICROMOUSE_MOTION_H_

#include "Arduino.h"
#include "config.h"
#include "encoding.h"
#include "motors.h"
#include "PIDController.h"

enum Direction { forward, backward };
enum MovementType {charge, search_arc, deploy_ramps, stop};

class Motion
{
private:
	Motor motor_l;
	Motor motor_r;
	
	PIDController pid_left;
	PIDController pid_right;
	
	MovementType movement_state;
	
	//Private motion functions
	void setVelRaw(Direction r, int pwmr, Direction l, int pwml);
	void setVel(float v, float w);
	
	void control_charge(int velocity);
	void control_search_arc(int velocity, int rotation);
	void control_deploy_ramps();

public:
  Motion();
	void charge();
	void search_arc();
	void deploy_ramps();
	
	//Must be called a set rate
	void update();

 };
 
#endif
