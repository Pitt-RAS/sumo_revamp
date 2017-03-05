#include "device/LineSensor.h"
#include "device/ProxSense.h"
#include "motion/motion.h"

class Robot
{
    private: 
        Motion sumo;
        int currentVelocity;
        int currentDirection; // 1 or -1
        int enemyDirection;   // 1 or -1
        int currentAngle;     // -90 to 90

        void updateSensors();

    public:
        Robot(LineSensor*, ProxSense*, ProxSense*, int);
            void executeState();

            LineSensor lineSensors;
            ProxSense frontProx;
            ProxSense rearProx;
            int currentState;
}; 
