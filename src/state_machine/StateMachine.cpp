#include "StateMachine.h"

void StateMachine::updateState() {

    sumo.update();
    motion.update();

    switch(current_state) {
        case CHARGE:
            if (!KAMIKAZE) {
                if (sumo.isWhite(sumo.getCurrentDirection(), 0)) {
                    current_state = GUARD_LINE;
                    break;
                }
            }
            if (!sumo.enemyInSight()) {
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
            if (sumo.enemyInSight()) {
                current_state = CHARGE;
            }
            break;
        case GUARD_LINE:
            if (!sumo.isWhite()) {
                current_state = CHARGE;
            }
            break;
    }
}

void StateMachine::executeState() {

    switch(current_state) {
        case CHARGE:
            motion.charge();
            break;
        case SEARCH:
            motion.search();
            break;        
        case GUARD_LINE:
            motion.guardLine();
            break;
    }
}

void StateMachine::deployRamps() {
    motion.deployRamps();
}
