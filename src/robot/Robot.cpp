#include "Robot.h"

////////// ROBOT //////////
void Robot::update() {
    prox.update();
    line.update();
    movement.update();
}

////////// PROXIMITY //////////
int Robot::getEnemyDirection() {
    return prox.getEnemyDirection();
}

int Robot::getEnemyAngle() {
    return prox.getEnemyAngle();
}

bool Robot::enemyInSight() {
    return prox.enemyInSight();
}

////////// LINE //////////
bool Robot::isWhite() {
    return line.isWhite(0, 0);
}

bool Robot::isWhite(int direction, int side) {
    return line.isWhite(direction, side);
}

////////// MOVEMENT //////////
void Robot::setDesiredVelocity(float desired_velocity) {
    movement.setDesiredVelocity(0, 0, desired_velocity);
}

void Robot::setDesiredVelocity(int side, float desired_velocity) {
    movement.setDesiredVelocity(0,  side, desired_velocity);
    movement.setDesiredVelocity(1,  side, desired_velocity);
    movement.setDesiredVelocity(-1, side, desired_velocity);
}

void Robot::setDesiredVelocity(int direction, int side, float desired_velocity) {
    movement.setDesiredVelocity(direction, side, desired_velocity);
}

int Robot::getCurrentDirection() {
    return movement.getCurrentDirection(0, 0);
}

int Robot::getCurrentDirection(int direction, int side) {
    return movement.getCurrentDirection(direction, side);
}

int Robot::getDesiredDirection() {
    return movement.getDesiredDirection(0, 0);
}

int Robot::getDesiredDirection(int direction, int side) {
    return movement.getDesiredDirection(direction, side);
}

float Robot::getCurrentVelocity() {
    return movement.getCurrentVelocity(0, 0);
}

float Robot::getCurrentVelocity(int direction, int side) {
    return movement.getCurrentVelocity(direction, side);
}

float Robot::getDesiredVelocity() {
    return movement.getDesiredVelocity(0, 0);
}

float Robot::getDesiredVelocity(int direction, int side) {
    return movement.getDesiredVelocity(direction, side);
}

float Robot::getVelocityError() {
    return movement.getVelocityError(0, 0);
}

float Robot::getVelocityError(int direction, int side) {
    return movement.getVelocityError(direction, side);
}

////////// ABSTRACTIONS //////////

// Uncomment when accelerometer is working, this is just to say if our acceleration is one standard devation different than we expect we are probably in contact with something

/*
bool Robot::possiblyInContact() {
    if (enemy_direction == 1) {
        if (current_acceleration < desired_acceleration * 0.66) {
            return true;
        }
    }
    else if (enemy_direction == -1) {
        if (current_acceleration > desired_acceleration * 0.66) {
            return true;
        }
    }
    else
    {
        if (current_acceleration < desired_acceleration * 0.66) {
            return true;
        }
        else if (current_accleration > desired_acceleration * 0.66) {
            return true;
        }
    }
    return false;
}
*/

bool Robot::possiblyLosing() {
    if ((getCurrentDirection() != getDesiredDirection())) {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::possiblyUnder() {
    if (!isWhite() || !enemyInSight()) {
        return false;
    }
    else
    {
        return isWhite(getEnemyDirection(), 0);
    }
}

/*
bool Robot::wheelsLostTraction() {
    // if one or two wheels have significantly different velocity than others return true
    
}
*/
