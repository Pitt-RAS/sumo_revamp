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
int proximity_sensors_front[5]        = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_front_weight[5] = {-90,         -45,         0,           45,          90};
int proximity_sensors_rear[5]  = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int proximity_sensors_rear_weight[5] = {-90,         -45,         0,           45,          90};

ProxSense frontProx(proximity_sensors_front, proximity_sensors_front_weight);
ProxSense rearProx(proximity_sensors_rear, proximity_sensors_rear_weight);

//Todo: initialize line sensor objects

Motor motor_l (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE);
Motor motor_r (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE);

Orientation* mpu = Orientation::getInstance();

void setup() {
	
  ///////////////Setting all necessary pinModes////////////////////////
  //LineSensing Pins
  pinMode(FR_LINESENSE_PIN, INPUT);
  pinMode(FL_LINESENSE_PIN, INPUT);
  pinMode(BL_LINESENSE_PIN, INPUT);
  pinMode(BR_LINESENSE_PIN, INPUT);
  
  //ProxSense Pins
  pinMode(F_PROX1_PIN, INPUT);
  pinMode(F_PROX2_PIN, INPUT);
  pinMode(F_PROX3_PIN, INPUT);
  pinMode(F_PROX4_PIN, INPUT);
  pinMode(F_PROX5_PIN, INPUT);
  
  pinMode(R_PROX1_PIN, INPUT);
  pinMode(R_PROX2_PIN, INPUT);
  pinMode(R_PROX3_PIN, INPUT);
  pinMode(R_PROX4_PIN, INPUT);
  pinMode(R_PROX5_PIN, INPUT);
  
  //Encoder Pins
  pinMode(FL_ENCODERB_PIN, INPUT);
  pinMode(FL_ENCODERA_PIN, INPUT);
  pinMode(BR_ENCODERA_PIN, INPUT);
  pinMode(FR_ENCODERB_PIN, INPUT);
  pinMode(BL_ENCODERA_PIN, INPUT);
  pinMode(BL_ENCODERB_PIN, INPUT);
  pinMode(FR_ENCODERA_PIN, INPUT);
  pinMode(BR_ENCODERB_PIN, INPUT);
  
  //Motor Pins
  pinMode(L_MOTOR_DIR_PIN, INPUT);
  pinMode(L_MOTOR_PWM_PIN, INPUT);
  pinMode(R_MOTOR_DIR_PIN, INPUT);
  pinMode(R_MOTOR_PWM_PIN, INPUT);
  
  //MISC
  pinMode(SIGNAL_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BATT_TEST_PIN, INPUT);
  
  //ToDo: Initialize IMU_INTERRUPT_PIN (Accelerometer) to a pinMode
  
  
  ///////////////////Beginning Other PreSetup Scripts//////////////////////
  //Turn off LED
  digitalWrite(SIGNAL_LED, 0);
 
 //Set Serial Baud for debugging
  Serial.begin(BAUD);

  // PWM resolution is 0-1023.
  analogWriteResolution(PWM_SPEED_BITS);

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
