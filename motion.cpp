#include "motion.h"

Motion::Motion()
	:motor_l (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE),
	motor_r (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE),
	pid_left (KP_POSITION, KI_POSITION, KD_POSITION),
	pid_right (KP_POSITION, KI_POSITION, KD_POSITION),
	flEn(FL_ENCODERA_PIN, FL_ENCODERB_PIN), //Front Left Encoder (1)
	frEn(FR_ENCODERA_PIN, FR_ENCODERB_PIN), //Front Right Encoder (2)
	blEn(BL_ENCODERA_PIN, BL_ENCODERB_PIN), //Back Left Encoder (3)
	brEn(BR_ENCODERA_PIN, BR_ENCODERB_PIN) //Back Right Encoder (4)
{

  //Setup the interrupt to call update
}

void Motion::update()
{
	//Update PID controllers
	//Compare current velocities to desired, using PID loop to calculate the new the settings to send to setVelRaw();
	float left_v = (flEn.stepRate() + blEn.stepRate())/2.0;
	float right_v = (frEn.stepRate() + brEn.stepRate())/2.0;

	int lpwm = pid_left.Calculate(left_v, target_left_v);
	int rpwm = pid_right.Calculate(right_v, target_right_v);
	setVelRaw(rpwm, lpwm);
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
	//Serial.println(flEn.stepRate() * 10000);
	setVel(v, 0);
}

void Motion::setVel(float v, float w){
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
	float vl = v + ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * w)/2.0); //Replace with trig to calculate the desired wheel speed.
	float vr = v - ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * w)/2.0); //Replace with trig to calculate the deisred wheel speed.
	/*
	Serial.print("v:");
	Serial.print(v);
	Serial.print("vl:");
	Serial.print(vl);
	Serial.print("vr:");
	Serial.print(vr);
	*/
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
	/*
	Serial.print("   pwml:");
	Serial.print(pwml);
	Serial.print("pwmr:");
	Serial.println(pwmr);
	*/
	//For now just set the pwm values
	setVelRaw(directionr, pwml, directionl, pwmr);
}

//Returns veloctiy of selected encoder
float Motion::EnVelocityFL(){
	 return (1000* flEn.stepRate() * MM_PER_STEP);
}
float Motion::EnVelocityFR(){
	 return (1000 * frEn.stepRate() * MM_PER_STEP);
}
float Motion::EnVelocityBL(){
	 return (1000 * blEn.stepRate() * MM_PER_STEP);
}
float Motion::EnVelocityBR(){
	 return (1000 * brEn.stepRate() * MM_PER_STEP);
}

//Private methods
void Motion::setVelRaw(int rpwm, int lpwm){
	bool r, l;
	if(rpwm > 0){
		r = true;
	}
	else {
		r =false;
	}
	if(lpwm){
		l = true;
	}
	else {
		l = false;
	}
	setVelRaw(r, abs(rpwm), l, abs(lpwm));
}

void Motion::setVelRaw(bool r, int pwmr, bool l, int pwml) {
	motor_r.SetRaw(r, pwmr);
	motor_l.SetRaw(l, pwml);
}
