#include "Movement.h"

Movement::Movement() {
    encoderFL(FL_ENCODERA_PIN, FL_ENCODERB_PIN);
    encoderFR(FR_ENCODERA_PIN, FR_ENCODERB_PIN);
    encoderBL(BL_ENCODERA_PIN, BL_ENCODERB_PIN);
    encoderBR(BR_ENCODERA_PIN, BR_ENCODERB_PIN);

    desired_velocity_FL = 0;
    desired_velocity_FR = 0;
    desired_velocity_BL = 0;
    desired_velocity_BR = 0;

    update();
}

void Movement::update() {
    current_velocity[2][2] = 1000 * encoderFL.stepRate() * MM_PER_STEP;
    current_velocity[2][0] = 1000 * encoderFR.stepRate() * MM_PER_STEP;
    current_velocity[0][2] = 1000 * encoderBL.stepRate() * MM_PER_STEP;
    current_velocity[0][0] = 1000 * encoderBR.stepRate() * MM_PER_STEP;
    current_velocity[2][1] = ((current_velocity[2][2] + current_velocity[2][0]) / 2.0);
    current_velocity[0][1] = ((current_velocity[0][2] + current_velocity[0][0]) / 2.0);
    current_velocity[1][2] = ((current_velocity[0][2] + current_velocity[2][2]) / 2.0);
    current_velocity[1][0] = ((current_velocity[0][0] + current_velocity[2][0]) / 2.0);
    current_velocity[1][1] = ((current_velocity[2][1] + current_velocity[0][1]) / 2.0);
}

void Movement::setDesiredVelocity(int direction, int side, float passed_desired_velocity) {
    desired_velocity[direction + 1][side + 1] = passed_desired_velocity;
}

float Movement::getCurrentVelocity(int direciton, int side) {
    return current_velocity[direction + 1][side + 1];
}

float Movement::getError(int direction, int side) {
    return current_velocity[direction + 1][side + 1] - desired_velocity[direction + 1][side + 1];
}

// bool Movement::liftedWheels() {
    // TODO
    // Only if wheels error corresponds to intended direction
    // Difference of two standard deviations
// }
