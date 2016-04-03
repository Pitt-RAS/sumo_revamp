#include <Arduino.h>

#include "config.h"
#include "encoding.h"
#include "motors.h"
#include "ProxSense.h"
#include "sensors_orientation.h"
#include <EncoderMod.h>
#include "I2Cdev.h"
#include "MPU9150.h"
#include "Logger.h"

//Create proximity sensor pin array initailize proximity sensors
int proximity_sensors_front[5] = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_rear[5]  = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};

//Todo: initialize line sensor objects

ProxSense frontProx(proximity_sensors_front);
ProxSense rearProx(proximity_sensors_rear);

Motor motor_l (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE);
Motor motor_r (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE);

Orientation* mpu = Orientation::getInstance();

void setup() {
  //Set the LED pin, turn it off for now
  pinMode(SIGNAL_LED, OUTPUT);
  digitalWrite(SIGNAL_LED, 0);

  Serial.begin(BAUD);

  // PWM resolution is 0-1023.
  analogWriteResolution(PWM_SPEED_BITS);
  
  //Misc
  #define ACCEL_INT_PIN 16

	//Setup button
	pinMode(BUTTON, INPUT);

  //Check Battery
  if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT){
    analogWriteFrequency(BUZZER_PIN, 2000);
    analogWrite(BUZZER_PIN, PWM_SPEED_STEPS / 2);
    delay(100000);
  }
}


//Regular code
#ifndef HARDWARE_TEST
void loop() {

}
#endif

//Hardware test code
#ifdef HARDWARE_TEST
void loop() {

}
#endif
