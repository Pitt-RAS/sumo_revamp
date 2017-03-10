#include <Arduino.h>
#include "StateMachine.h"
#include "../config.h"


StateMachine::StateMachine() {
    Robot sumo(motion);
    Motion motion(sumo);
}

void StateMachine::updateState() {

    sumo.update();

    switch(current_state) {
        case CHARGE:
            if (!KAMIKAZE) {
                if (sumo.hitLineInDirection(current_direction)) {
                    current_state = GUARD_LINE;
                    break;
                }
            }
            if (!sumo.enemy_in_sight) {
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
            if (sumo.enemy_in_sight) {
                current_state = CHARGE;
            }
            break;
        case GUARD_LINE:
            if (!sumo.on_line) {
                current_state = CHARGE;
            }
            break;
    }
}

void StateMachine::executeState() {

    switch(current_state) {
        case CHARGE:
            sumo.charge();
            break;
        case SEARCH:
            sumo.search();
            break;        
        case GUARD_LINE:
            sumo.guardLine();
            break;
    }
}
