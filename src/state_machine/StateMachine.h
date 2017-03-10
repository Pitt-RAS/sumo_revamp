#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "../config.h"
#include "../motion/motion.h"
#include "../robot/Robot.h"


class StateMachine
{
    private: 
        Robot sumo;
        Motion motion;

        int current_state;
        int cycle;

    public:
        StateMachine(int starting_state) :
            sumo(),
            motion(sumo) {
                current_state = starting_state;
                cycle = 0;
            } 

        int getState();
        void updateState();
        void executeState();
        void deployRamps();
}; 

#endif
