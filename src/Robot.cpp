#include "Robot.h"

Robot::Robot(Motion& passedMotion) {
    motion = passedMotion;
    frontProx({F_PROX_PIN, F_PROX2_PIN, F_PROX3_PIN, F_PROX4_PIN, F_PROX5_P    IN},
              {-90,        -45,         0,           45,          90             });
    rearProx ({R_PROX_PIN, R_PROX2_PIN, R_PROX3_PIN, R_PROX4_PIN, R_PROX5_P    IN},                  
              {-90,        -45,         0,           45,          90             });

    LineSense lineSensors(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_    PIN, BR_LINESENSE_PIN);
   
    encoderFL(FL_ENCODERA_PIN, FL_ENCODERB_PIN);
    encoderFR(FR_ENCODERA_PIN, FR_ENCODERB_PIN);
    encoderBL(BL_ENCODERA_PIN, BL_ENCODERB_PIN);
    encoderBR(BR_ENCODERA_PIN, BR_ENCODERB_PIN);
}

void Robot::update() {
    updateProx();
    updateLine();
}


void Robot:updateProx() {
    front_angle = frontProx.readAngle();
    rear_angle  = rearProx.readAngle();

    if (front_angle != PROXIMITY_INACTIVE && rear_angle != PROXIMITY_INACTIVE) {
        // We see something on both sides so we will refer to our previous readings which entails doing nothing here, if we get more sophistcated we will detect which is closer to us and call that the true enemy direction
        if (enemy_direction == 1) {
            enemy_angle = front_angle;
        } else if (enemy_direction == -1) {
            enemy_angle = rear_angle;
        }
        enemy_in_sight = true;
    } 
    else if (front_angle != PROXIMITY_INACTIVE) 
    {
        enemy_angle = front_angle;
        enemy_direction = 1;
        enemy_in_sight = true;
        
    }
    else if (rear_angle != PROXIMITY_INACTIVE)
    {
        enemy_angle = rear_angle;
        enemy_direction = -1;
        enemy_in_sight = true;
    }
    else
    {
        enemy_angle = PROXIMITY_INACTIVE;
        enemy_direction = 0;
        enemy_in_sight = false;
    }
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

void Robot::updateEncoders() {
    current_velocity_FL = 1000 * encoderFL.stepRate() * MM_PER_STEP;
    current_velocity_FR = 1000 * encoderFR.stepRate() * MM_PER_STEP;
    current_velocity_BL = 1000 * encoderBL.stepRate() * MM_PER_STEP;
    current_velocity_BR = 1000 * encoderBR.stepRate() * MM_PER_STEP;

    desired_velocity = motion.getDesiredVelocity();
    desired_velocity_FL = motion.getDesiredVelocityOfLeft();
    desired_velocity_BL = desired_velocity_FL;
    desired_velocity_FR = motion.getDesiredVelocityofRight();
    desired_velocity_BR = desired_velocity_FR;


    error_FL = desired_velocity_FL - current_velocity_FL;
    error_FR = desired_velocity_FR - current_velocity_FR;
    error_BL = desired_velocity_BL - current_velocity_BL;
    error_BR = desired_velocity_BR - current_velocity_BR;
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
    float average_velocity = (current_velocity_FL + current_velocity_FR + current_velocity_BL + current_velocity_BR);
    average_velocity /= 4.0;
    if (average_velocity > 0) {
        return 1;
    }
    else if (average_velocity < 0)
    {
        return -1;
    }
    else 
    {
        return 0;
    }
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
    if ((current_direction != desired_direction)) {
        return true;
    }
    else
    {
        return false;
    }
}

bool Robot::possiblyUnder() {
    if (!on_line || !enemy_in_sight) {
        return false;
    }
    else
    {
        return lineInDirection(enemy_direction);
    }
}

/*
bool Robot::wheelsLostTraction() {
    // if one or two wheels have significantly different velocity than others return true
    
}
*/
