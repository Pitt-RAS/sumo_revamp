#ifndef ROBOT_H
#define ROBOT_H

#include "../device/LineSense.h"
#include "../device/ProxSense.h"
#include "../motion/motion.h"
#include "Enemy.h"


class Robot
{
    private: 
        Motion sumo;
        int currentVelocity;
        int currentDirection; // 1 or -1
        int enemyDirection;   // 1 or -1
        int currentAngle;     // -90 to 90


    public:
        Robot(Motion& sumoInput, LineSense& lineSensorsInput, Enemy& opponentInput, int startingState) :
            sumo(sumoInput), lineSensors(lineSensorsInput), opponent(opponentInput), currentState(startingState) {}


        void updateSensors();
        void updateState();
        void executeState();

        LineSense lineSensors;
        Enemy opponent;
        
        int currentState;
}; 

#endif
