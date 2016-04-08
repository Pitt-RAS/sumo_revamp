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
#include "motion.h"

//Turn on off test driver
#define TEST_DRIVER

//Create proximity sensor pin array initailize proximity sensors
int proximity_sensors_front[5]        = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_front_weight[5] = {-90,         -45,         0,           45,          90};
int proximity_sensors_rear[5]  = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int proximity_sensors_rear_weight[5] = {-90,         -45,         0,           45,          90};

ProxSense frontProx(proximity_sensors_front, proximity_sensors_front_weight);
ProxSense rearProx(proximity_sensors_rear, proximity_sensors_rear_weight);

//Initialize motion control object
Motion sumo;

//Todo: initialize line sensor objects

//Orientation* mpu = Orientation::getInstance();

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
  pinMode(L_MOTOR_DIR_PIN, OUTPUT);
  pinMode(L_MOTOR_PWM_PIN, OUTPUT);
  pinMode(R_MOTOR_DIR_PIN, OUTPUT);
  pinMode(R_MOTOR_PWM_PIN, OUTPUT);
  analogWrite(L_MOTOR_PWM_PIN, 0);
  analogWrite(R_MOTOR_PWM_PIN, 0);
  
  //MISC
  pinMode(SIGNAL_LED_PIN, OUTPUT);
  digitalWrite(SIGNAL_LED_PIN, 0);
  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(BUZZER_PIN, 0);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(IMU_INTERRUPT_PIN, INPUT);
  
  
  ///////////////////Beginning Other PreSetup Scripts//////////////////////
 
 //Set Serial Baud for debugging
  Serial.begin(BAUD);
  
  // PWM resolution is 0-1023.
  analogWriteResolution(PWM_SPEED_BITS);
  

  //Check Battery
  if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT){
    tone(BUZZER_PIN, 2000);
  }
  
  // Set higher pwm frequency for smoother motor control.
  analogWriteFrequency(L_MOTOR_PWM_PIN, 46875);
  analogWriteFrequency(R_MOTOR_PWM_PIN, 46875);
  
}

#ifndef TEST_DRIVER
void loop() {
  Serial.println("Looping new");
  sumo.setVel(0, 1);
  delay(1000);

  sumo.setVel(0, -1);
  delay(1000);

  sumo.setVel(0);  
  delay(4000);
  /*
	//Read sensors
	int prox_front_error = frontProx.readAngle();
	int prox_rear_error = rearProx.readAngle();
	
	//For debugging
	Serial.print("front:");
	Serial.print(prox_front_error);
	Serial.print("    ");
	Serial.print("rear:");
	Serial.println(prox_rear_error);
	*/
	/*
	//WIP all signs will need to be set through testing
	//These constants should be in config.h, however for now they will be here until the signs are all set.
	int CHARGE_VEL = 512;
	int FUDGE_FACTOR = 1;
	//Set possible movements
	//Prioritize the front over the rear
	if(prox_front_error != PROXIMITY_INACTIVE){
		sumo.setVel(CHARGE_VEL, prox_front_error * FUDGE_FACTOR);
	}
	else if(prox_rear_error != PROXIMITY_INACTIVE){
		sumo.setVel(-CHARGE_VEL, prox_front_error * FUDGE_FACTOR);
	}
	*/

}
#endif


#ifdef TEST_DRIVER

#define TEST_PROX
//#define TEST_MOTORS_ENC

void loop() {
	
#ifdef TEST_PROX
	Serial.print("front: ");
	for(int ii = 0; ii < 5; ii++)
	{
		Serial.print(digitalRead(proximity_sensors_front[ii]));
	}
	Serial.print("    back:");
	
	for(int ii = 0; ii < 5; ii++)
	{
		Serial.print(digitalRead(proximity_sensors_rear[ii]));
	}
	Serial.println();
#endif

#ifdef TEST_MOTORS_ENC
	//Motors should go forward, all encoders give positive velocities
	Serial.println("forward");
	sumo.setVel(512);
	delay(500);
	Serial.print("FL: ");
	Serial.print(EnVelocityFL());
	Serial.print(" FR: ");
	Serial.print(EnVelocityFL());
	Serial.print(" BL: ");
	Serial.print(EnVelocityFL());
	Serial.print(" BR: ");
	Serial.print(EnVelocityBR());
	delay(100);
	sumo.setVel(0);
	delay(2000);

	
	//Motors should go backward, all encoders give positive velocities
	Serial.println("backward");
	sumo.setVel(-512);
	delay(500);
	Serial.print("FL: ");
	Serial.print(EnVelocityFL());
	Serial.print(" FR: ");
	Serial.print(EnVelocityFL());
	Serial.print(" BL: ");
	Serial.print(EnVelocityFL());
	Serial.print(" BR: ");
	Serial.print(EnVelocityBR());
	delay(100);
	sumo.setVel(0);
	delay(2000);
#endif

}
#endif
