#include "motion.h"

void Motion::update() {
    sumo.setDesiredVelocity(desired_velocity_net);
    sumo.setDesiredVelocity(1,  desired_velocity_left);
    sumo.setDesiredVelocity(-1, desired_velocity_right);

    current_velocity_left  = sumo.getCurrentVelocity(0,  1);
    current_velocity_right = sumo.getCurrentVelocity(0, -1);

	float modified_velocity_left  = pidLeft.Calculate (current_velocity_left,  desired_velocity_left);
	float modified_velocity_right = pidRight.Calculate(current_velocity_right, desired_velocity_right);
	setVelRaw(modified_velocity_left, 0);
}

//Public state setting methods
void Motion::charge() {
	setVel(CHARGE_VELOCITY * sumo.getEnemyDirection(), FUDGE_FACTOR * sumo.getEnemyAngle());
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


void Motion::setVel(float input_desired_velocity_net, float angle_of_turn) {
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
    desired_velocity_net = input_desired_velocity_net;
	desired_velocity_left  = desired_velocity_net + ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * angle_of_turn)/2.0); //Replace with trig to calculate the desired wheel speed.
	desired_velocity_right = desired_velocity_net - ((PI * DISTANCE_BETWEEN_WHEELS * (1024.0/ 1.5) * angle_of_turn)/2.0); //Replace with trig to calculate the deisred wheel speed.
}


//Private methods
void Motion::setVelRaw(float velocity_left, float velocity_right){
    bool left_going_forward;
	bool right_going_forward;
	if(velocity_left > 0){
		left_going_forward = true;
	}
	else {
		left_going_forward = false;
	}
	if(velocity_right > 0){
		right_going_forward = true;
	}
	else {
		right_going_forward = false;
	}
    // motorLeft.SetRaw (left_going_forward,  abs(velocity_left));
    // motorRight.SetRaw(right_going_forward, abs(velocity_right));
}

void Motion::testVel(float input_velocity) {
    setVel(input_velocity, 0);
}
