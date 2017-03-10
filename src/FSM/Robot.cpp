#include <Arduino.h>
#include "Robot.h"
#include "../config.h"

void Robot::updateSensors() {
    lineSensors.update();
    opponent.update();
    currentDirection = sumo.getCurrentDirection();
}

void Robot::updateState() {

    ///////////// Interperet ProxSense, determine enemyDirection and enemyAngle /////////////
    /*
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
    */

    switch(current_state) {
        case CHARGE:
            if (!KAMIKAZE) {
                if (lineSensors.hitLineInDirection(currentDirection)) {
                    current_state = GUARD_LINE;
                    break;
                }
            }
            if (!opponent.in_sight) {
                current_state = SEARCH;
            } else {
                current_state = CHARGE;
            }
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
            if (opponent.in_sight) {
                current_state = CHARGE;
            }
            break;
        case GUARD_LINE:
            if (!lineSensors.on_line) {
                current_state = CHARGE;
            }
            break;
    }
}

void Robot::executeState() {
    switch(current_state) {
        case CHARGE:
            sumo.charge();
            break;
        case SEARCH:
            sumo.search();
            break;        
        case GUARD_LINE:
            sumo.guardLine();
    }
}
