#include <Arduino.h>

#include "config.h"
#include "ProxSense.h"

int front_pin_array[5] = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int rear_pin_array[5]  = {R_PROX1_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_PIN};
int weight_array[5]    = {-90,         -45,         0,           45,          90         };

ProxSense frontProx(front_pin_array, weight_array);
ProxSense rearProx(rear_pin_array,  weight_array);
 
void setup()
{ 
  pinMode(SIGNAL_LED_PIN, OUTPUT);
  digitalWrite(SIGNAL_LED_PIN, 0);
  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(BUZZER_PIN, 0);
  pinMode(BUTTON_PIN, INPUT_PULLUP);


  ///////////////////Beginning Other PreSetup Scripts//////////////////////

  //Set Serial Baud for debugging baud=bits per second
  Serial.begin(BAUD);

  // PWM resolution is 0-1023. wanted more than default
  analogWriteResolution(PWM_SPEED_BITS);

  //Set Serial Baud for debugging baud=bits per second
  Serial.begin(BAUD);

  //Check Battery
  if(analogRead(BATT_TEST_PIN) <= BATTERY_VOLTAGE_WARNING_COUNT)
  {
    tone(BUZZER_PIN, 2000);
  }

}
void loop()
{   
   //Serial.println("FRONT:");
  //int front_angle = frontProx.readAngle();
  Serial.println("REAR:");
  int rear_angle = rearProx.readAngle();


  /*Serial.print("Front Angle: \t");
  Serial.println(front_angle);
  Serial.print("\nRear Angle: \t");
  Serial.println(rear_angle);*/
  
  delay(500);
}
