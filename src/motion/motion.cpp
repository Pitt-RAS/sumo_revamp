#include "motion.h"

void Motion::update()
{
	//Update PID controllers
	//Compare current velocities to desired, using PID loop to calculate the new the settings to send to setVelRaw();
	//float left_v = ((flEn.stepRate() + blEn.stepRate())/2.0) * 1000.0 * MM_PER_STEP;
	float left_v = ((blEn.stepRate())) * 1000.0 * MM_PER_STEP;
	float right_v = ((frEn.stepRate() + brEn.stepRate())/2.0)  * 1000.0 * MM_PER_STEP;

	int lpwm = pid_left.Calculate(left_v, target_left_v);
	int rpwm = pid_right.Calculate(right_v, target_right_v);

	setVelRaw(rpwm, lpwm);
}
//Public state setting methods
void Motion::charge()
{
	setVel(CHARGE_VELOCITY * opponent.direction, FUDGE_FACTOR * opponent.getAngle()); //Go forward not rotation
}

void Motion::search()
{
	setVel(1.0, 0.2); //10 m/s, 10rad/s rotation
}

void Motion::guardLine() {
    setVel(CHARGE_VELOCITY * opponent.direction * -1, FUDGE_FACTOR * opponent.getAngle() * -1); // charge directly away from them
}

void Motion::deployRamps()
{
	setVelRaw(1024, -1024);
	delay(100); //Deploys the plows
	setVelRaw(0, 0);
	delay(200);
}

void Motion::setVel(float v){
	//Serial.println(flEn.stepRate() * 10000);
	setVel(v, 0);
}

void Motion::setVel(float v, float w){
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
	float vl = v + ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * w)/2.0); //Replace with trig to calculate the desired wheel speed.
	float vr = v - ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * w)/2.0); //Replace with trig to calculate the deisred wheel speed.
	target_left_v = v + w;
	target_right_v = v - w;
	
	/*
	Serial.print("v:");
	Serial.print(v);
	Serial.print("vl:");
	Serial.print(vl);
	Serial.print("vr:");
	Serial.print(vr);
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
	Serial.print("   pwml:");
	Serial.print(pwml);
	Serial.print("pwmr:");
	Serial.println(pwmr);
	//or now just set the pwm values
	setVelRaw(directionr, pwml, directionl, pwmr);
	*/
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

int Motion::getCurrentDirection() {
    float averageVelocity = (flEn.stepRate() + frEn.stepRate() + blEn.stepRate() + brEn.stepRate()) / 4.0;
    if (averageVelocity > 0) {
        return FRONT;
    } else if (averageVelocity < 0) {
        return REAR;
    } else {
        return 0;
    }
}

//Private methods
void Motion::setVelRaw(int rpwm, int lpwm){
	bool r, l;
	if(rpwm > 0){
		r = true;
	}
	else {
		r = false;
	}
	if(lpwm > 0){
		l = true;
	}
	else {
		l = false;
	}
    motor_r.SetRaw(r, abs(rpwm));
    motor_l.SetRaw(l, abs(lpwm));
}

