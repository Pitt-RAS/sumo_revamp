#include <Arduino.h>

#include "motors.h"

#include "config.h"

Motor::Motor(int motor_f_pin, int motor_f_pwm_pin, bool motor_f_forward_state){
	pin_ = motor_f_pin;
	pwm_pin_ = motor_f_pwm_pin;
	forward_state_ = motor_f_forward_state;

	//initializes pins for motors
	pinMode(pin_, OUTPUT);
	pinMode(pwm_pin_, OUTPUT);
	
}


// input desired force and current speed
static float idealMotorOutput(float force, float velocity) {
    float required_current = force / FORCE_PER_AMP; 
    float back_emf = velocity / VELOCITY_PER_VBEMF;
    return ((required_current * RATED_INTERNAL_RESISTANCE + back_emf) / BATTERY_VOLTAGE);
}


void Motor::Set(float acceleration, float current_velocity) {
    float force;
    float speed;
    int pin_state;
    int speed_raw;

    if (current_velocity > 0) {
        force = (ROBOT_MASS * acceleration + FRICTION_FORCE) / NUMBER_OF_MOTORS;
    } else if (current_velocity < 0) {
        force = (ROBOT_MASS * acceleration - FRICTION_FORCE) / NUMBER_OF_MOTORS;
    } else {
        force = (ROBOT_MASS * acceleration) / NUMBER_OF_MOTORS;
    }

    speed = idealMotorOutput(force, current_velocity);
    speed = constrain(speed, -1, 1);

    speed_raw = abs((int)(round(PWM_SPEED_STEPS * speed)));

    if (speed > 0.0) {
        pin_state = HIGH;
    } else {
        pin_state = LOW;
    }

    digitalWrite(pin_, pin_state ^ forward_state_ ^ 1);
    analogWrite(pwm_pin_, speed_raw);
}

void Motor::SetRaw(bool forward, int speed_raw) {
    if (forward) {
        digitalWrite(pin_, HIGH);
    }
    else {
        digitalWrite(pin_, LOW);
    }
    analogWrite(pwm_pin_, speed_raw);
}
