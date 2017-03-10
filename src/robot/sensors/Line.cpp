#include "Line.h"

void Line::update() {
    is_white[2][2] = !digitalRead(FL_PIN);
    is_white[2][0] = !digitalRead(FR_PIN);
    //is_white[0][2] = !digitalRead(BL_PIN);
    //is_white[0][0] = !digitalRead(BR_PIN);
    is_white[0][2] = false;
    is_white[0][0] = false;

    is_white[2][1] = is_white[2][2] || is_white[2][0];
    is_white[0][1] = is_white[0][2] || is_white[0][0];
    is_white[1][2] = is_white[2][2] || is_white[0][2];
    is_white[1][0] = is_white[2][0] || is_white[0][0];

    is_white[1][1] = is_white[2][1] || is_white[0][1];
}

bool Line::isWhite(int direction, int side) {
    return is_white[direction + 1][side + 1];
}
