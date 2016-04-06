#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>


//Uncomment to enable the hardware test and disable normal operation
//#define HARDWARE_TEST

//*************************** Define pin assignments for teensy3.2 on Rev1 PCB ******************************************
// FR = Front Right | FL = Front Left | BR = Back Right | BL = Back Left
/*Undefined Pins
	13
*/

//BlueTooth Pins
#define BT_TX 0
#define BT_RX 1
#define BAUD 115200

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
#define FR_ENCODERB_PIN 27
#define BL_ENCODERA_PIN 28
#define BL_ENCODERB_PIN 29
#define FR_ENCODERA_PIN 30
#define BR_ENCODERB_PIN 31

//Motor Pins
#define L_MOTOR_DIR_PIN 20 //A6
#define L_MOTOR_PWM_PIN 21 //A7
#define L_MOTOR_FORWARD_STATE true
#define R_MOTOR_DIR_PIN 17 //A3
#define R_MOTOR_PWM_PIN 22 //A8
#define R_MOTOR_FORWARD_STATE true

#define PWM_SPEED_BITS 10
#define PWM_SPEED_STEPS 1023 // = 2^PWM_SPEED_BITS

//Misc
#define SIGNAL_LED_PIN 13
#define IMU_INTERRUPT_PIN 16 //(Accelerometer)
#define BUZZER_PIN 23
#define BUTTON_PIN 33

//Battery Level Testing
#define BATT_TEST_PIN A10
#define BATTERY_VOLTAGE_WARNING 7.7
#define BATTERY_VOLTAGE_DIVIDER_RATIO (10.0/(10.0+20.0)) // Vdd -- 20K -- VBat -- 10K -- GND
#define BATTERY_VOLTAGE_WARNING_COUNT (BATTERY_VOLTAGE_WARNING * (1023.0/3.3) * BATTERY_VOLTAGE_DIVIDER_RATIO)

// Logging configuration
#define LOG_SIZE 500

// Gyro parameters
#define GYRO_LSB_PER_DEG_PER_S 16.295
#define GYRO_CALIBRATION_SAMPLES 2000
#define GYRO_CALIBRATION_ROUNDS 3
#define GYRO_OFFSET_SETTING -43
#define GYRO_SECONDARY_OFFSET 11.0050

// Accelerometer parameters
#define ACCEL_LSB_PER_G 2048

// Magnetometer parameters
#define MAG_CYCLES_PER_UPDATE 5
#define MAG_COMPLEMENTARY_FILTER 0.00

// Motor stop failsafe parameters
#define FAILSAFE_GYRO_THRESHOLD 100 // in deg/s
#define FAILSAFE_GYRO_ANGLE 20 // in deg
#define FAILSAFE_ACCEL_THRESHOLD 10// in mg


////BELOW HAS NOT YET BEEN UPDATED/////////

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
#define ROBOT_MASS .500 // kilograms
#define MM_BETWEEN_WHEELS 85.5 // millimeters
#define NUMBER_OF_MOTORS 4
#define STEPS_PER_MOTOR_REV 12// the number of encoder steps we get per wheel revolution
#define BATTERY_VOLTAGE 8.1 // Volts
//#define MAX_ACCEL_STRAIGHT 4 // m/s/s
//#define MAX_DECEL_STRAIGHT -4 // m/s/s
//#define MAX_ACCEL_ROTATE 3 // m/s/s  
//#define MAX_DECEL_ROTATE -3 // m/s/s
//#define MAX_ACCEL_CORNER 3 // m/s/s  
//#define MAX_DECEL_CORNER -3 // m/s/s


<<<<<<< HEAD
#define GEAR_RATIO 29.86 // gear ratio between motor and wheels
=======
#define GEAR_RATIO 9.96 // gear ratio between motor and wheels
>>>>>>> origin/master
#define MAX_VEL_STRAIGHT 0.5 // m/s   limited by the maximum velocity at which motors can deliver max accel

// Motor spec sheet parameters
#define RATED_VOLTAGE 8 // Voltage that ratings were measured with
#define RATED_INTERNAL_RESISTANCE 3.1 // ohms of resistance in motor coils
#define RATED_FREERUN_CURRENT 0.06// Amps
<<<<<<< HEAD
#define RATED_RPM_PER_VBEMF 818000 // RPM/Volt
=======
#define RATED_RPM_PER_VBEMF (3000.0/6.0) // RPM/Volt
>>>>>>> origin/master
#define RATED_TORQUE_PER_AMP 0.000622353 // torque in N-m at output shaft, Amps passed through motor

// Convert motor parameters to robot parameters
#define WHEEL_RADIUS (MM_PER_STEP * STEPS_PER_MOTOR_REV * GEAR_RATIO / (2 * 3.14159265359))// in millimeters
<<<<<<< HEAD
#define FORCE_PER_AMP (RATED_TORQUE_PER_AMP * GEAR_RATIO * NUMBER_OF_MOTORS * 1000 / WHEEL_RADIUS) // in Newtons
=======
#define FORCE_PER_AMP (RATED_TORQUE_PER_AMP * GEAR_RATIO * 1000 / WHEEL_RADIUS) // in Newtons
>>>>>>> origin/master
#define VELOCITY_PER_VBEMF (RATED_RPM_PER_VBEMF * STEPS_PER_MOTOR_REV * GEAR_RATIO * MM_PER_STEP / (60000)) // 60000 is for mm to m and s to min
#define FRICTION_FORCE (RATED_FREERUN_CURRENT * FORCE_PER_AMP + 0.10) // Newtons (0.08 calculated Newtons from motor/gearbox)  amount of force opposing motion in robot including rolling resistance, sliding, gearing

//  TODO precompile, calculate max velocity based on turn radius and max accel, which will then limit max velocity through centripital force.  
//    if this max velocity is higher than max straight velocity then use max straight velocity
#define MAX_VEL_ROTATE 0.1 // m/s
#define MAX_VEL_CORNER .5 // m/s

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> origin/master
