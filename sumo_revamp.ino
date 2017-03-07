#include <Arduino.h>

#include <EncoderPittMicromouse.h>

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
#include "src/FSM/Robot.h"
#include "src/FSM/Enemy.h"
// Motion
#include "src/motion/motion.h"

const bool display = false;
const bool competition = false;

// Create the Enemy object abstraction from proximity sensors
    // Create proximity sensor pin array and weights
int proximity_sensors_front[5]        = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_front_weight[5] = {-90,         -45,         0,           45,          90};
int proximity_sensors_rear[5]         = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int proximity_sensors_rear_weight[5]  = {-90,         -45,         0,           45,          90};

    // Create the ProxSense objects
ProxSense frontProx(proximity_sensors_front, proximity_sensors_front_weight);
ProxSense rearProx (proximity_sensors_rear,  proximity_sensors_rear_weight);
//const ProxSense& frontProxRef = frontProx;
//const ProxSense& rearProxRef  = rearProx;

    // Create the Enemy object
Enemy opponent(frontProx, rearProx);
//const Enemy& opponentRef = opponent;

// Line Sensors
LineSense lineSensors(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_PIN, BR_LINESENSE_PIN);
//const LineSense& lineSensorsRef = lineSensors;

// Motion Control object
Motion sumo(opponent, lineSensors);
//const Motion& sumoRef = sumo;

// Robot FSM object
Robot stateMachine(sumo, lineSensors, opponent, CHARGE);

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
    sumo.deployRamps();
}

void loop(){
    if (!competition && analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT) {
        tone(BUZZER_PIN, 2000);
    }

    stateMachine.updateSensors();
    stateMachine.updateState();
    stateMachine.executeState();

    sumo.update(); // what does update pid loop mean?
}
