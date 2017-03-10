#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "motion/motion.h"
#include "Robot.h"


class StateMachine
{
    private: 
        Motion motion;
        Robot sumo;

        int current_velocity;
        int current_direction; // 1 or -1
        int enemy_direction;   // 1 or -1
        int current_angle;     // -90 to 90
        int current_state;


    public:
        StateMachine();

        int getState();
        void updateState();
        void executeState();
}; 

#endif
