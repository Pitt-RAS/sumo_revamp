#include <Arduino.h>

#include "config.h"
#include "LineSensor.h"

//construct line sensors
LineSensor lineSensors(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_PIN, BR_LINESENSE_PIN);

void setup() 
{
  //MISC pins
  pinMode(SIGNAL_LED_PIN, OUTPUT);
  digitalWrite(SIGNAL_LED_PIN, 0);
  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(BUZZER_PIN, 0);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  //Set Serial Baud for debugging baud=bits per second
  Serial.begin(BAUD);

  // PWM resolution is 0-1023. wanted more than default
  analogWriteResolution(PWM_SPEED_BITS);

  //Check Battery
  if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT)
  {
    tone(BUZZER_PIN, 2000);
  }
}

void loop() 
{
  Serial.print("FL: ");
    Serial.print(digitalRead(FL_LINESENSE_PIN));
    Serial.print(" FR: ");
    Serial.print(digitalRead(FR_LINESENSE_PIN));
    Serial.print(" BL: ");
    Serial.print(digitalRead(BL_LINESENSE_PIN));
    Serial.print(" BR: ");
    Serial.println(digitalRead(BR_LINESENSE_PIN));
    delay(10);  //Slight delay for the console

}
