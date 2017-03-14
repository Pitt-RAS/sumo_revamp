#include <Arduino.h>
#include "src/config.h"
#include "src/Accelerometer.h"

void setup() {
  Serial.begin(BAUD);
}

void loop() {

  Accelerometer accel;

  accel.update();

  float Xaccel = accel.getXAccel();
  float Yaccel = accel.getYAccel();

   Serial.print("X: ");
   Serial.println(Xaccel);
   Serial.println();
   Serial.print("Y: ");
   Serial.println(Yaccel);

   delay(50);
   
}
