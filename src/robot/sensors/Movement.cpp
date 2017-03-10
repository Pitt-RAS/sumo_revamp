#include "Movement.h"

void Movement::update() {
    // Every index should be subtracted by 1 to indicate direction and side properly
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
    // Garunteed to be updated during the Robot update phase from the Motion class 
    desired_velocity[direction + 1][side + 1] = passed_desired_velocity;
}



int Movement::getCurrentDirection(int direction, int side) {
    if (current_velocity[direction + 1][side + 1] > 0) {
        return 1;
    }
    else if (current_velocity[direction + 1][side + 1] < 0) 
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int Movement::getDesiredDirection(int direction, int side) {
    if (desired_velocity[direction + 1][side + 1] > 0) {
        return 1;
    }
    else if (desired_velocity[direction + 1][side + 1] < 0) 
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

float Movement::getCurrentVelocity(int direction, int side) {
    return current_velocity[direction + 1][side + 1];
}

float Movement::getDesiredVelocity(int direction, int side) {
    return desired_velocity[direction + 1][side + 1];
}

float Movement::getVelocityError(int direction, int side) {
    return current_velocity[direction + 1][side + 1] - desired_velocity[direction + 1][side + 1];
}
