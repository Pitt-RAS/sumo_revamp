#include "motion.h"

Motion::Motion(Robot& passedSumo) {
    sumo = passedSumo;
    encoderFL = sumo.encoderFL;
    encoderFR = sumo.encoderFR;
    encoderBL = sumo.encoderBL;
    encoderBR = sumo.encoderBR;

    motorLeft  (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE),
    motorRight (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE),
    pidLeft  (KP_POSITION, KI_POSITION, KD_POSITION),
    pidRight (KP_POSITION, KI_POSITION, KD_POSITION),

    target_velocity_left  = 0;
    target_velocity_right = 0;
}


//Public state setting methods
void Motion::charge()
{
	setVel(CHARGE_VELOCITY * sumo.getEnemyDirection, FUDGE_FACTOR * sumo.getEnemyAngle());
}


void Motion::search() {
	setVel(SEARCH_VELOCITY, 0.2);
}


void Motion::guardLine() {
    setVel(CHARGE_VELOCITY * sumo.getEnemyDirection() * -1, FUDGE_FACTOR * sumo.getEnemyAngle() * -1); // charge directly away from them
}


void Motion::deployRamps() {
	setVelRaw(1024, -1024);
	delay(100); //Deploys the plows
	setVelRaw(0, 0);
	delay(200);
}


void Motion::setVel(float net_velocity, float angle_of_turn) {
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
	desired_velocity_left  = net_velocity + ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * angle_of_turn)/2.0); //Replace with trig to calculate the desired wheel speed.
	desired_velocity_right = net_velocity - ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * angle_of_turn)/2.0); //Replace with trig to calculate the deisred wheel speed.

	int modified_velocity_left  = pidLeft.Calculate (current_velocity_left,  desired_velocity_left);
	int modified_velocity_right = pidRight.Calculate(current_velocity_right, target_velocity_right);
	setVelRaw(modified_velocity_left, modified_velocity_right);
}


//Private methods
void Motion::setVelRaw(int velocity_right, int velocity_right){
	bool r, l;
	if(velocity_left > 0){
		l = true;
	}
	else {
		l = false;
	}
	if(velocity_right > 0){
		r = true;
	}
	else {
		r = false;
	}
    motor_r.SetRaw(r, abs(rpwm));
    motor_l.SetRaw(l, abs(lpwm));
}

