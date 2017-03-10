#include <Arduino.h>

#include <EncoderPittMicromouse.h>

#include "config.h"

#include "motors.h"
#include "motion.h"

//Initialize motion control object
Motion sumo;

void setup() 
{
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
	if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT)
	{
		tone(BUZZER_PIN, 2000);
	}
	
	while (digitalRead(BUTTON_PIN))
	{
		Serial.println("button!");
		sumo.update();  // need to update pid loop (why?)
		delay(10); // possibly to prevent sumo.update from being called too often
	}
	delay(5000);
	sumo.deploy_ramps();
}

void loop() 
{
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
}
