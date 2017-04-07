#include <Arduino.h>
#include <EncoderPittMicromouse.h>
#include "config.h"
#include "motors.h"

const bool competition = false;

 Motor motorLeft(L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE);
 Motor motorRight(R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE);


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


    waitForButton();
}

void loop(){
    if (!competition && analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT) {
        tone(BUZZER_PIN, 2000);
    }

    motorLeft.SetRaw(true, 512);
    motorRight.SetRaw(true, 512);

    delay(2000);

    motorLeft.SetRaw(true, 0);
    motorRight.SetRaw(true, 0);

    while(true)
    {
       motorLeft.SetRaw(true, 0);
       motorRight.SetRaw(true, 0);
    }



}

void waitForButton(){
    //Button Press
    Serial.println("Waiting for Button");
    while (digitalRead(BUTTON_PIN)){
        delay(10); // possibly to prevent sumo.update from being called too often
    }
    Serial.println("Button Pressed");
    delay(5000);
}


