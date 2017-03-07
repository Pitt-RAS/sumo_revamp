#include <Arduino.h>

#include "config.h"
#include "ProxSense.h"
#include "Printing.h"

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
    Printing();
}
