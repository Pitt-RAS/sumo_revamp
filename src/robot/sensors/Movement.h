#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <EncoderPittMicromouse.h>
#include "../config.h"

class Movement
{
    private:
        EncoderPittMicromouse encoderFL;
        EncoderPittMicromouse encoderFR;
        EncoderPittMicromouse encoderBL;
        EncoderPittMicromouse encoderBR;

        float current_velocity[3][3];
        float desired_velocity[3][3];
    public:
        Movement();

        void update();

        void setDesiredVelocity(int, int, float);

        int getCurrentDirection(int, int);
        int getDesiredDirection(int, int);
        float getCurrentVelocity(int, int);
        float getDesiredVelocity(int, int);
        float getVelocityError(int, int);
}
#endif
