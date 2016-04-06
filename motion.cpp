#include "motion.h"

Motion::Motion()
	:motor_l (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE),
	motor_r (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE),
	pid_left (KP_POSITION, KI_POSITION, KD_POSITION),
	pid_right (KP_POSITION, KI_POSITION, KD_POSITION)
{
	movement_state = stop;

  //Setup the interrupt to call update
}

void Motion::update()
{
	//Compare current velocities to desired, using PID loop to calculate the new the settings to send to setVelRaw();
	switch(movement_state){
		case MovementType::charge:
			control_charge();
			break;
		case MovementType::search_arc:
			control_search_arc();
			break;
		case MovementType::deploy_ramps:
			deploy_ramps();
			break;
		case MovementType::stop:
			break;
	}
}
//Public state setting methods
void Motion::charge()
{
	movement_state = MovementType::charge;
}

void Motion::search_arc()
{
	movement_state = MovementType::search_arc;
}

void Motion::deploy_ramps()
{
	movement_state = MovementType::deploy_ramps;
}
//Private methods
void Motion::setVelRaw(Direction r, int pwmr, Direction l, int pwml){
	//Actually set things to the motor 
}

void Motion::setVel(int v, float w){
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
}

void Motion::control_charge()
{
	
}

void Motion::control_search_arc()
{
	
}

void Motion::control_deploy_ramps()
{
	
}