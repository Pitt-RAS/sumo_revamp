#include <Arduino.h>
#include "../config.h"
#include "LineSense.h"

void LineSense::update() {
      is_white_FL = !digitalRead(FL_PIN);
      is_white_FR = !digitalRead(FR_PIN);
      is_white_BL = !digitalRead(BL_PIN);
      is_white_BR = !digitalRead(BR_PIN);

      on_line = is_white_FL || is_white_FR || is_white_BL || is_white_BR;
}

bool LineSense::hitLineInDirection(int direction) {
    if (direction == FRONT) {
        return (is_white_FL || is_white_FR);
    } else if (direction == REAR) {
        return (is_white_BL || is_white_BR);
    } else {
        return false;
    }
}
