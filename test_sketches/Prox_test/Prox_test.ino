#include <Arduino.h>

#include "config.h"
#include "ProxSense.h"

int proximity_sensors_front[5]        = {F_PROX1_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_PIN};
int proximity_sensors_front_weight[5] = {-90,         -45,         0,           45,          90};

ProxSense frontProx(proximity_sensors_front, proximity_sensors_front_weight);

void setup() 
{ 
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
    int prox_front_error = frontProx.readAngle();

    Serial.println(prox_front_error);

    delay(100);
}
