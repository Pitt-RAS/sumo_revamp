#include <Arduino.h>
#include "src/config.h"
#include "src/Accelerometer.h"

void setup() {
  Serial.begin(BAUD);
}

void loop() {

  Accelerometer accel;

  accel.update();

  float forward = accel.getMaxForwardAccel();
  float radial = accel.getMaxRadialAccel();

   Serial.print("Forward: ");
   Serial.println(forward);
   Serial.println();
   Serial.print("Radial: ");
   Serial.println(radial);

   delay(500);
   
}
