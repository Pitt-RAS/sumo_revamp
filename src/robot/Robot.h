#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "../config.h"
#include "sensors/Proximity.h"
#include "sensors/Line.h"
#include "sensors/Movement.h"
#include <EncoderPittMicromouse.h>

class Robot
{
    private:
        Movement movement;
        Proximity prox;
        Line line;

    public:
        Robot();

        void update();

        int getEnemyAngle();
        int getEnemyDirection();
        bool enemyInSight();

        bool isWhite();
        bool isWhite(int, int);


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

        // bool possiblyInContact();
        bool possiblyLosing();
        bool possiblyUnder();
        // bool wheelsLostTraction();
}


