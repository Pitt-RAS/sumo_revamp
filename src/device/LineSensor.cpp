#include <Arduino.h>
#include "../config.h"
#include "LineSensor.h"

LineSensor::LineSensor() {
      pinMode(FL_LINESENSE_PIN, INPUT);
      pinMode(FR_LINESENSE_PIN, INPUT);
      pinMode(BL_LINESENSE_PIN, INPUT);
      pinMode(BR_LINESENSE_PIN, INPUT);
      update();
}

void LineSensor::update() {
      isWhiteFL = !digitalRead(FL_LINESENSE_PIN);
      isWhiteFR = !digitalRead(FR_LINESENSE_PIN);
      isWhiteBL = !digitalRead(BL_LINESENSE_PIN);
      isWhiteBR = !digitalRead(BR_LINESENSE_PIN);
}
