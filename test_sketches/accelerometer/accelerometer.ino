#include <Arduino.h>
#include "src/config.h"
#include "src/Accelerometer.h"

void setup() {
  Serial.begin(BAUD);
}

void loop() {

  Accelerometer accel;

  while (true)
  {
     accel.update();

 /* float Xaccel = accel.getXAccel();
  float Yaccel = accel.getYAccel();

   Serial.print("X: ");
   Serial.println(Xaccel);
   Serial.println();
   Serial.print("Y: ");
   Serial.println(Yaccel);
*/
  bool collision = accel.collision();

    if (collision)
   {
     Serial.println("COLLISION");
   }
   else 
    {
     Serial.println();
    }


     delay(50);
  }
}
