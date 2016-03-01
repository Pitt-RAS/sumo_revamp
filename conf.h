#ifndef CONF_H
#define CONF_H

#include <Arduino.h>

//*************************** Define pin assignments for teensy3.2 on Rev1 PCB ******************************************
// FR = Front Right | FL = Front Left | BR = Back Right | BL = Back Left
/*Undefined Pins
	13
	33
*/

//BlueTooth Pins
#define BT_RX 0
#define BT_RX 1

//LineSensing Pins
#define FR_LINESENSE_PIN 2
#define FL_LINESENSE_PIN 3
#define BL_LINESENSE_PIN 4
#define BR_LINESENSE_PIN 5

//ProxSense Pins
#define F_PROX1_PIN 7
#define F_PROX2_PIN 6
#define F_PROX3_PIN 24
#define F_PROX4_PIN 25
#define F_PROX5_PIN 32
#define R_PROX1_PIN 12
#define R_PROX2_PIN 11
#define R_PROX3_PIN 10
#define R_PROX4_PIN 9
#define R_PROX5_PIN 8

//Encoder Pins
#define FL_ENCODERB_PIN 14
#define FL_ENCODERA_PIN 15
#define BR_ENCODERA_PIN 26
#define BR_ENCODERB_PIN 27
#define BL_ENCODERA_PIN 28
#define BL_ENCODERB_PIN 29
#define FR_ENCODERA_PIN 30
#define FR_ENCODERB_PIN 31

//Motor Pins
#define R_MOTOR_DIR_PIN A3 //17
#define L_MOTOR_DIR_PIN A6 //20
#define L_MOTOR_PWM_PIN A7 //21
#define R_MOTOR_PWM_PIN A8 //22

//Misc
#define ACCEL_INT_PIN 16
#define SDA0_PIN 18
#define SCL0_PIN 19
#define BUZZER_PIN 23
#define BATT_TEST_PIN A10

////BELOW HAS NOT YET BEEN UPDATED/////////


// RANGE SENSOR OPTIONS

// Range sensor directions
#define RANGE_DIAG_LEFT_PIN RANGE1_PIN
#define RANGE_DIAG_RIGHT_PIN RANGE2_PIN
#define RANGE_LEFT_PIN RANGE3_PIN
#define RANGE_RIGHT_PIN RANGE4_PIN
#define RANGE_FRONT_PIN RANGE5_PIN

// Range sensor distance offsets
#define RANGE_DIAG_LEFT_OFFSET -35
#define RANGE_DIAG_RIGHT_OFFSET -35
#define RANGE_LEFT_OFFSET 15
#define RANGE_RIGHT_OFFSET 15
#define RANGE_FRONT_OFFSET 30

// Range sensor wall thresholds
#define RANGE_DIAG_LEFT_WALL_THRESHOLD 75
#define RANGE_DIAG_RIGHT_WALL_THRESHOLD 75
#define RANGE_LEFT_WALL_THRESHOLD 70
#define RANGE_RIGHT_WALL_THRESHOLD 70
#define RANGE_FRONT_WALL_THRESHOLD 125

#define LEFT_LOW_THRESHOLD 50
#define LEFT_HIGH_THRESHOLD 100
#define RIGHT_LOW_THRESHOLD 50
#define RIGHT_HIGH_THRESHOLD 100

// Range sensor middle readings
#define RANGE_DIAG_LEFT_MIDDLE 80
#define RANGE_DIAG_RIGHT_MIDDLE 80
#define RANGE_LEFT_MIDDLE 100
#define RANGE_RIGHT_MIDDLE 100
#define RANGE_FRONT_MIDDLE 100

// Number of samples in moving average
#define RANGE_QUEUE_MAX_LENGTH 10
#define HISTORY_QUEUE_MAX_LENGTH 100

// Number of old samples to clear when wall status changes
#define RANGE_QUEUE_NUM_TO_CLEAR 5

// Motion control paremeters
#define MM_PER_BLOCK 180
#define MM_PER_STEP 0.6444

// PID tuning parameters
#define KP_POSITION 5.69
#define KI_POSITION 0
#define KD_POSITION 0

#define KP_ROTATION 1
#define KI_ROTATION 0
#define KD_ROTATION 0

// Robot characteristics
#define ROBOT_MASS .226 // kilograms
#define MM_BETWEEN_WHEELS 85.5 // millimeters
#define NUMBER_OF_MOTORS 2
#define STEPS_PER_MOTOR_REV 12// the number of encoder steps we get per wheel revolution
#define BATTERY_VOLTAGE 8.1 // Volts
#define MAX_ACCEL_STRAIGHT 4 // m/s/s
#define MAX_DECEL_STRAIGHT -4 // m/s/s
#define MAX_ACCEL_ROTATE 3 // m/s/s  
#define MAX_DECEL_ROTATE -3 // m/s/s
#define MAX_ACCEL_CORNER 3 // m/s/s  
#define MAX_DECEL_CORNER -3 // m/s/s


#define GEAR_RATIO 9.96 // gear ratio between motor and wheels
#define MAX_VEL_STRAIGHT 0.5 // m/s   limited by the maximum velocity at which motors can deliver max accel
#define PWM_SPEED_STEPS 1023 // maximum PWM value for the system

// Motor spec sheet parameters
#define RATED_VOLTAGE 8 // Voltage that ratings were measured with
#define RATED_INTERNAL_RESISTANCE 3.1 // ohms of resistance in motor coils
#define RATED_FREERUN_CURRENT 0.06// Amps
#define RATED_RPM_PER_VBEMF 818000 // RPM/Volt
#define RATED_TORQUE_PER_AMP 0.000622353 // torque in N-m at output shaft, Amps passed through motor

// Convert motor parameters to robot parameters
#define WHEEL_RADIUS (MM_PER_STEP * STEPS_PER_MOTOR_REV * GEAR_RATIO / (2 * 3.14159265359))// in millimeters
#define FORCE_PER_AMP (RATED_TORQUE_PER_AMP * GEAR_RATIO * NUMBER_OF_MOTORS * 1000 / WHEEL_RADIUS) // in Newtons
#define VELOCITY_PER_VBEMF (RATED_RPM_PER_VBEMF * STEPS_PER_MOTOR_REV * GEAR_RATIO * MM_PER_STEP / (60000)) // 60000 is for mm to m and s to min
#define FRICTION_FORCE (RATED_FREERUN_CURRENT * FORCE_PER_AMP + 0.10) // Newtons (0.08 calculated Newtons from motor/gearbox)  amount of force opposing motion in robot including rolling resistance, sliding, gearing

//  TODO precompile, calculate max velocity based on turn radius and max accel, which will then limit max velocity through centripital force.  
//    if this max velocity is higher than max straight velocity then use max straight velocity
#define MAX_VEL_ROTATE 0.1 // m/s
#define MAX_VEL_CORNER .5 // m/s

#endif
