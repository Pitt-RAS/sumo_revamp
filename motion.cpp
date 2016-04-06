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
	//Update PID controllers
	//Compare current velocities to desired, using PID loop to calculate the new the settings to send to setVelRaw();
	
	//Below is probably not needed, I'll think about it in the morning
	/*switch(movement_state){
		case MovementType::charge:
			control_charge();
			break;
		case MovementType::search_arc:
			control_search_arc();
			break;
		case MovementType::deploy_ramps:
			control_deploy_ramps();
			break;
		case MovementType::stop:
			setVel(0, 0);
			break;
	}*/
}
//Public state setting methods
void Motion::charge()
{
	//movement_state = MovementType::charge
	setVel(10, 0); //Go forward not rotation
}

void Motion::search_arc()
{
	//movement_state = MovementType::search_arc;
	setVel(10, 10); //10 m/s, 10rad/s rotation
}

void Motion::deploy_ramps()
{
	//movement_state = MovementType::deploy_ramps;
	
	setVel(0, 30);//Spin
	delay(500); //Delay
	setVel(0, 0); //Stop
}
//Private methods
void Motion::setVelRaw(Direction r, int pwmr, Direction l, int pwml){
	//Actually set things to the motor 
}

void Motion::setVel(float v, float w){
	//Do work to calculate individual motor velocities from angular acceleration and centerline velocity
	Direction directionl, directionr;

	
	
	float vl = v + ((PI * DISTANCE_BETWEEN_WHEELS * w)/2.0); //Replace with trig to calculate the desired wheel speed.
	float vr = v - ((PI * DISTANCE_BETWEEN_WHEELS * w)/2.0); //Replace with trig to calculate the deisred wheel speed.
	
	if(vl > 0){
		directionl = Direction::forward;
	}
	else{
		directionl = Direction::backward;
	}
	
	if(vr > 0){
		directionr = Direction::forward;
	}
	else{
		directionr = Direction::backward;
	}
	
	//Set the PID controllers to the v that is being targeted
	//For now just fudge it!
	
	int pwml = abs(vl) * (1024/1.0);
	int pwmr = abs(vr) * (1024/1.0);

	//For now just set the pwm values
	setVelRaw(directionr, pwml, directionl, pwmr);
}

//These might not be needed
void Motion::control_charge()
{
	//setVel(10, 0); //Go forward not rotation
}

void Motion::control_search_arc()
{
	
}

void Motion::control_deploy_ramps()
{
	
}