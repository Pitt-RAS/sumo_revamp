#include <Arduino.h>
#include "Robot.h"
#include "config.h"

Robot::Robot (LineSensor* lineSensors, ProxSense* frontProx, ProxSense* rearProx, int startingState) {

    lineSensors = LineSensor(starting variables);
    lineSensors = *passedLineSensors;
    frontProx = *passedFrontProx;
    rearProx = *passedrearProx;

    currentState = startingState;
}

Robot::updateSensors() {
    lineSensors.update();
    int frontProxAngle = frontProx.readAngle();
    int rearProxAngle = rearProx.readAngle();
}

Robot::updateState() {

    updateSensors();
    ///////////// Interperet ProxSense, determine enemyDirection and enemyAngle /////////////
    if (frontProxAngle != PROXIMITY_INACTIVE && rearProxAngle == PROXIMITY_INACTIVE) {
        enemyDirection = 1;
        enemyAngle = frontProxAngle;
    }
    else if (rearProxAngle != PROXIMITY_INACTIVE && frontProxAngle == PROXIMITY_INACTIVE) {
        enemyDirection = -1;
        enemyAngle = rearProxAngle;
    }
    else if (frontProxAngle == PROXIMITY_INACTIVE && rearProxAngle == PROXIMITY_INACTIVE) {
       // they're gone, we still know they're prev direction fron enemyDirection
    }
    else { // Both sides see something, going with last known direction
        if (enemyDirection == 1) {
            enemyAngle = frontProxAngle;
        } else {
            enemyAngle = rearProxAngle;
        }
    }

    switch(currentState) {
        case CHARGE:

    
            

            
            break;
        case SHOVE: //if in front and encoders not at desired velocity (by certain amount, maybe consider previous velocity in case just accelerating)

            break;
        case RECOVER: //if previously charging and no longer in view
            // We should set our velocity lower and turn either towards them or away
            // how should we turn to look for them, potentially turn away to see them with the other ramp 
            break;
        case RETREAT: //if shoving and losing

            break;
        case EVADE: //if retreating and some condition to hypothesize

            break;
        case SEARCH: // if unseen
            
            break;
    }
}

Robot::executeState() {
    switch(currentState) {
        case CHARGE:
            sumo.setVel(CHARGE_VEL * enemyDirection, frontProxAngle * turnConstant);
            break;
        case SHOVE:
            // Completely unused rn
            break;
        case RECOVER:
            
    }
}

Robot::charge() {
    
