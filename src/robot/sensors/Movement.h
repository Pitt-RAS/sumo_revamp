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

        float getCurrentVelocity(int, int);
        float getDesiredVelocity(int, int);
        void  setDesiredVelocity(int, int, float);
        float getError(int, int);
}
#endif
