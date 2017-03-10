#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "../config.h"
#include "sensors/Proximity.h"
#include "sensors/Line.h"
#include "sensors/Movement.h"

class Robot
{
    private:
        Movement movement;
        Proximity prox;
        Line line;

    public:
        // ROBOT
        Robot() :
            movement(),
            prox(),
            line(FL_LINESENSE_PIN, FR_LINESENSE_PIN, BL_LINESENSE_PIN, BR_LINESENSE_PIN) {}

        void update();

        // PROXIMITY
        int getEnemyDirection();
        int getEnemyAngle();
        bool enemyInSight();

        // LINE
        bool isWhite();
        bool isWhite(int, int);

        // MOVEMENT
        void setDesiredVelocity(float);
        void setDesiredVelocity(int, float);
        void setDesiredVelocity(int, int, float);

        int getCurrentDirection();
        int getCurrentDirection(int, int);

        int getDesiredDirection();
        int getDesiredDirection(int, int);

        float getCurrentVelocity();
        float getCurrentVelocity(int, int);

        float getDesiredVelocity();
        float getDesiredVelocity(int, int);

        float getVelocityError();
        float getVelocityError(int, int);

        // ABSTRACTIONS
        // bool possiblyInContact();
        bool possiblyLosing();
        bool possiblyUnder();
        // bool wheelsLostTraction();
};
#endif
