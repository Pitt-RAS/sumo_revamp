#include "motion.h"

Motion::Motion()
	:motor_l (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE),
	motor_r (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE),
	pid_left (KP_POSITION, KI_POSITION, KD_POSITION),
	pid_right (KP_POSITION, KI_POSITION, KD_POSITION)
{

  //Setup the interrupt to call update
}

void Motion::update()
{
	//Update PID controllers
	//Compare current velocities to desired, using PID loop to calculate the new the settings to send to setVelRaw();
}
//Public state setting methods
void Motion::charge()
{
	setVel(CHARGE_VELOCITY, 0); //Go forward not rotation
}

void Motion::search_arc()
{
	setVel(SEARCH_ARC_VELOCITY, SEARCH_ARC_ROTATION); //10 m/s, 10rad/s rotation
}

void Motion::deploy_ramps()
{
	//movement_state = MovementType::deploy_ramps;
	
	setVel(0, 512);//Spin
	delay(500); //Delay
	setVel(0, 0); //Stop
}

void Motion::setVel(float v){
	setVel(v, 0);
}

void Motion::setVel(float v, float w){
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
	float vl = v + ((PI * DISTANCE_BETWEEN_WHEELS * w)/2.0); //Replace with trig to calculate the desired wheel speed.
	float vr = v - ((PI * DISTANCE_BETWEEN_WHEELS * w)/2.0); //Replace with trig to calculate the deisred wheel speed.
	
	bool directionl, directionr;
	if(vl >= 0){
		directionl = true;
	}
	else{
		directionl = false;
	}
	
	if(vr >= 0){
		directionr = true;
	}
	else{
		directionr = false;
	}
	
	//Set the PID controllers to the v that is being targeted
	//For now just fudge it!
	
	int pwml = abs(vl);
	if(pwml > 1023)	
		pwml = 1023;
	int pwmr = abs(vr);
	if(pwmr > 1023)	
		pwmr = 1023;

	//For now just set the pwm values
	setVelRaw(directionr, pwml, directionl, pwmr);
}

//Private methods
void Motion::setVelRaw(bool r, int pwmr, bool l, int pwml) {
	motor_r.SetRaw(r, pwmr);
	motor_l.SetRaw(l, pwml);
}
