#include "Robot.h"

Robot::Robot() {
    frontProx({F_PROX_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_P    IN},
              {-90,        -45,         0,           45,          90             });
    rearProx ({R_PROX_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_P    IN},                  
              {-90,        -45,         0,           45,          90             });

    Line line(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_PIN, BR_LINESENSE_PIN);

    Movement movement();
}

void Robot::update() {
    motion.update(); // for desired velocities
    prox.update();
    line.update();
    movement.update();
}

bool Robot::isWhite() {
    return line.isWhite(0, 0);
}

bool Robot::isWhite(int direction, int side) {
    return line.isWhite(direction, side);
}

int Robot::getCurrentDirection() {
    return movement.getCurrentDirection(0, 0);
}

int Robot::getCurrentDirection(int direction, int side) {
    return movement.getCurrentDirection(direction, side);
}

int Robot::getDesiredDirection() {
    return Movement.getDesiredDirection(0, 0);
}

int Robot::getDesiredDirection(int direction, side) {
    return Movement.getDesiredDirection(direction, side);
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
    return movement.getError(0, 0);
}

float Robot::getVelocityError(int direction, int side) {
    return movement.getVelocityError(direction, side);
}

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
    if ((movement.getCurrentDirection() != movement.getDesiredDirection())) {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::possiblyUnder() {
    if (!line.onLine || !prox.enemyInSight()) {
        return false;
    }
    else
    {
        return line.lineInDirection(prox.getEnemyDirection());
    }
}

/*
bool Robot::wheelsLostTraction() {
    // if one or two wheels have significantly different velocity than others return true
    
}
*/
