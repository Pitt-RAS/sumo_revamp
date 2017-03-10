#include <EncoderPittMicromouse.h>
#include <Arduino.h>
#include "src/config.h"

// Devices
#include "src/device/motors.h"
#include "src/device/ProxSense.h"
#include "src/device/sensors_orientation.h"
#include "src/device/I2Cdev.h"
#include "src/device/MPU9150.h"
#include "src/device/LineSense.h"
// Debugging
#include "src/debugging/Logger.h"
// FSM
#include "src/StateMachine.h"
#include "src/Robot.h"
// Motion
#include "src/motion/motion.h"

const bool display = false;
const bool competition = false;

// Robot object
Robot sumo();

// Motion Control object
Motion motion(opponent, lineSensors);

// Robot FSM object
StateMachine stateMachine();

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
    Serial.println("Waiting for Button");
    while (digitalRead(BUTTON_PIN)){
        sumo.update();  // need to update pid loop (why?)
        delay(10); // possibly to prevent sumo.update from being called too often
    }
    Serial.println("Button Pressed");
    delay(5000);
    motion.deployRamps();
}

void loop(){
    if (!competition && analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT) {
        tone(BUZZER_PIN, 2000);
    }

    stateMachine.updateState();
    stateMachine.executeState();

    motion.update(); // what does update pid loop mean?
}
