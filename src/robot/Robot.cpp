#include "Robot.h"

Robot::Robot(Motion& passedMotion) {
    motion = passedMotion;
    frontProx({F_PROX_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_P    IN},
              {-90,        -45,         0,           45,          90             });
    rearProx ({R_PROX_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_P    IN},                  
              {-90,        -45,         0,           45,          90             });

    Line lineSensors(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_    PIN, BR_LINESENSE_PIN);

    Movement movement();
}

void Robot::update() {
    motion.update(); // for desired velocities
    prox.update();
    line.update();
    movement.update();
}


void Robot::updateLine() {
    lineSensors.update();

    is_white_FL = lineSensors.is_white_FL;
    is_white_FR = lineSensors.is_white_FR;
    is_white_BL = lineSensors.is_white_BL;
    is_white_BR = lineSensors.is_white_BR;

    is_white_F  = is_white_FL || is_white_FR;
    is_white_B  = is_white_BL || is_white_BR;
    is_white_L  = is_white_FL || is_white_BL;
    is_white_R  = is_White_FR || is_white_BR;

    on_line     = is_white_F || is_white_B;
}

int Robot::getLineDirection() {
    if (!on_line) {
        return 0;
    }
    else if (is_white_F && !is_white_B) 
    {
        return 1;
    }
    else if (is_white_B && !is_white_F)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

bool Robot::lineInDirection(int passed_direction) {
    if (passed_direction = 1) {
        return is_white_F;
    }
    else if (passed_direction = -1)
    {
        return is_white_B;
    }
    else 
    {
        return false;
    }
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
