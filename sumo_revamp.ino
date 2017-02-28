#include <Arduino.h>

#include <EncoderPittMicromouse.h>

#include "src/config.h"

#include "src/device/motors.h"
#include "src/device/ProxSense.h"
#include "src/device/sensors_orientation.h"
#include "src/device/I2Cdev.h"
#include "src/device/MPU9150.h"
#include "src/device/LineSensor.h"

#include "src/debugging/Logger.h"

#include "src/motion/motion.h"

//Turn on off test driver
//#define TEST_DRIVER

static bool display = false;

//Create proximity sensor pin array initailize proximity sensors
int proximity_sensors_front[5]        = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_front_weight[5] = {-90,         -45,         0,           45,          90};
int proximity_sensors_rear[5]  = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int proximity_sensors_rear_weight[5] = {-90,         -45,         0,           45,          90};

ProxSense frontProx(proximity_sensors_front, proximity_sensors_front_weight);
ProxSense rearProx(proximity_sensors_rear, proximity_sensors_rear_weight);

//Initialize motion control object
Motion sumo;

//construct line sensors
LineSensor lineSensors(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_PIN, BR_LINESENSE_PIN);

//Orientation* mpu = Orientation::getInstance();

void setup() { 

  //MISC pins
  pinMode(SIGNAL_LED_PIN, OUTPUT);
  digitalWrite(SIGNAL_LED_PIN, 0);
  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(BUZZER_PIN, 0);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(IMU_INTERRUPT_PIN, INPUT);


  ///////////////////Beginning Other PreSetup Scripts//////////////////////

  //Set Serial Baud for debugging baud=bits per second
  Serial.begin(BAUD);

  // PWM resolution is 0-1023. wanted more than default
  analogWriteResolution(PWM_SPEED_BITS);

  // Set higher pwm frequency for smoother motor control.
  analogWriteFrequency(L_MOTOR_PWM_PIN, 46875);
  analogWriteFrequency(R_MOTOR_PWM_PIN, 46875);

  //Check Battery
  if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT){
    tone(BUZZER_PIN, 2000);
  }

  //Button Press
  //setVelRaw(-1024, 1024);
  while (digitalRead(BUTTON_PIN)){
    Serial.println("button!");
    sumo.update();  // need to update pid loop (why?)
    delay(10); // possibly to prevent sumo.update from being called too often
  }
  delay(5000);
  sumo.deploy_ramps();
}

#ifndef TEST_DRIVER // this is the main loop
  void loop(){
    // COMMENT OUT THE NEXT 3 LINES FOR COMPETITION! check battery during tests
    if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT){ //***NOTE: does && Display count here***//
      tone(BUZZER_PIN, 2000);
    }

    lineSensors.update();
    Serial.println(lineSensors.isWhiteFL);
    bool FL_Line = !lineSensors.isWhiteFL;
    bool FR_Line = !lineSensors.isWhiteFR;
    bool BL_Line = !lineSensors.isWhiteBL;
    bool BR_Line = !lineSensors.isWhiteBR;

    //Read sensors
    int prox_front_error = frontProx.readAngle();
    int prox_rear_error = rearProx.readAngle();

    //For debugging
    /*Serial.print("front:");
    Serial.print(prox_front_error);
    Serial.print("    ");
    Serial.print("rear:");
    Serial.println(prox_rear_error);
    */
    //prox_rear_error = PROXIMITY_INACTIVE;
    //prox_front_error = PROXIMITY_INACTIVE;

    //WIP all signs will need to be set through testing

    static float CURRENT_VEL = CHARGE_VEL;
    static bool CURRENT_VEL_DIRECTION = true; //true = forward false = backward

    delay(1);  // ????
    //Set possible movements
    //Prioritize the front over the rear
    
    if(!(FL_Line || FR_Line || BL_Line || BR_Line)){
      sumo.setVel(0, 0);
      //Stop 4ever
      while(1){
      sumo.update();
      delay(1);
      }
    }
    // charge forward
    else if(prox_front_error != PROXIMITY_INACTIVE){  // as long as something is seen
      if (display) {
      sumo.setVel(0, 0);
      } else {
      sumo.setVel(CHARGE_VEL, prox_front_error * FUDGE_FACTOR);
      }
    }
    // charge backwards
    else if(prox_rear_error != PROXIMITY_INACTIVE)
    {
      if (display)
      {
      sumo.setVel(0, 0);
      }
      else
      {
        sumo.setVel(-CHARGE_VEL, prox_rear_error * FUDGE_FACTOR);
      }
    }
    else if(!FL_Line || !FR_Line) //Line Checking
    {
      if(CURRENT_VEL_DIRECTION){
        CURRENT_VEL = -CURRENT_VEL;
        CURRENT_VEL_DIRECTION = false;  // prevents repeatedly hitting the line
      }
      sumo.setVel(CURRENT_VEL,0);
    }
    else if(!BL_Line || !BR_Line)
    {
      if(!CURRENT_VEL_DIRECTION){
        CURRENT_VEL = -CURRENT_VEL;
        CURRENT_VEL_DIRECTION = true;
      }
      sumo.setVel(CURRENT_VEL,0);
    }
    else if(!FL_Line){
      sumo.setVel(-0.5 * CHARGE_VEL, -3);  // mess around with .5 constant, it's limited by if we prioritize rotational or charge velocity
    }
    else if(!FR_Line){
      sumo.setVel(-0.5 * CHARGE_VEL, 3);
    }
    else if(!BL_Line){
      sumo.setVel(0.5 * CHARGE_VEL,  3);
    }
    else if(!BR_Line){
      sumo.setVel(0.5 * CHARGE_VEL, -3);
    } else {
      if (display) {
        sumo.setVel(0, 0);
      } 
      else {
        sumo.setVel(CURRENT_VEL, 0.2 * (abs(CURRENT_VEL) / 1.0));
      }
    }
    sumo.update(); //Must be called so that PID loop gets updated
  }
#endif


#ifdef TEST_DRIVER

#define TEST_PROX
//#define TEST_MOTORS_ENC
//#define TEST_LINE_SENSORS

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
    Serial.print("forward   ");
    sumo.setVelRaw(512, 512);
    delay(1000);
    Serial.print("FL: ");
    Serial.print(sumo.EnVelocityFL());
    Serial.print(" FR: ");
    Serial.print(sumo.EnVelocityFR());
    Serial.print(" BL: ");
    Serial.print(sumo.EnVelocityBL());
    Serial.print(" BR: ");
    Serial.println(sumo.EnVelocityBR());
    delay(100);
    sumo.setVelRaw(0, 0);
    delay(2000);

    //Motors should go backward, all encoders give positive velocities
    Serial.print("backward   ");
    sumo.setVelRaw(-512, -512);
    delay(1000);
    Serial.print("FL: ");
    Serial.print(sumo.EnVelocityFL());
    Serial.print(" FR: ");
    Serial.print(sumo.EnVelocityFR());
    Serial.print(" BL: ");
    Serial.print(sumo.EnVelocityBL());
    Serial.print(" BR: ");
    Serial.println(sumo.EnVelocityBR());
    delay(100);
    sumo.setVelRaw(0, 0);
    delay(2000);
  #endif

  #ifdef TEST_LINE_SENSORS
    Serial.print("FL: ");
    Serial.print(digitalRead(FL_LINESENSE_PIN));
    Serial.print(" FR: ");
    Serial.print(digitalRead(FR_LINESENSE_PIN));
    Serial.print(" BL: ");
    Serial.print(digitalRead(BL_LINESENSE_PIN));
    Serial.print(" BR: ");
    Serial.println(digitalRead(BR_LINESENSE_PIN));
    delay(10);  //Slight delay for the console

  #endif
}
#endif
