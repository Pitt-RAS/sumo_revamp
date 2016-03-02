#include <Arduino.h>
#include "config.h"
#include "motors.h"

// input desired force and current speed
static float idealMotorOutput(float force, float velocity) {
  float required_current, back_emf;
  required_current = force / FORCE_PER_AMP;
  back_emf = velocity / VELOCITY_PER_VBEMF;
  return ((required_current * RATED_INTERNAL_RESISTANCE + back_emf) / BATTERY_VOLTAGE);
}

Motor motor_l (L_MOTOR_DIR_PIN, MOTOR_A2_PIN, L_MOTOR_PWM_PIN);
Motor motor_r (R_MOTOR_DIR_PIN, MOTOR_B2_PIN, R_MOTOR_PWM_PIN);

Motor::Motor(int pin1, int pin2, int pwm_pin) {
  pin1_ = pin1;
  pin2_ = pin2;
  pin_pwm_ = pwm_pin;

  pinMode(pin1_, OUTPUT);
  pinMode(pin2_, OUTPUT);
  pinMode(pin_pwm_, OUTPUT);
}

void Motor::Set(float accel, float current_velocity) {
  float force;
  float speed;
  int pin1_state, pin2_state;
  int speed_raw;

  if (current_velocity > 0) {
    force = (ROBOT_MASS * accel + FRICTION_FORCE) / NUMBER_OF_MOTORS;
  } else if (current_velocity < 0) {
    force = (ROBOT_MASS * accel - FRICTION_FORCE) / NUMBER_OF_MOTORS;
  } else {
    force = (ROBOT_MASS * accel) / NUMBER_OF_MOTORS;
  }

  speed = idealMotorOutput(force, current_velocity);
  speed = constrain(speed, -1, 1);

  speed_raw = abs((int)(round(PWM_SPEED_STEPS * speed)));

  if (speed > 0.0) {
    pin1_state = HIGH;
    pin2_state = LOW;
  } else if (speed < 0.0) {
    pin1_state = LOW;
    pin2_state = HIGH;
  } else {
    pin1_state = LOW;
    pin2_state = LOW;
  }

  digitalWrite(pin1_, pin1_state);
  digitalWrite(pin2_, pin2_state);
  analogWrite(pin_pwm_, speed_raw);
}
