#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <EncoderPittMicromouse.h>
#include "../../config.h"

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
        Movement() :
            encoderFL(FL_ENCODERA_PIN, FL_ENCODERB_PIN),
            encoderFR(FR_ENCODERA_PIN, FR_ENCODERB_PIN),
            encoderBL(BL_ENCODERA_PIN, BL_ENCODERB_PIN),
            encoderBR(BR_ENCODERA_PIN, BR_ENCODERB_PIN) {
                update();
            }

        void update();

        void setDesiredVelocity(int, int, float);

        int getCurrentDirection(int, int);
        int getDesiredDirection(int, int);
        float getCurrentVelocity(int, int);
        float getDesiredVelocity(int, int);
        float getVelocityError(int, int);
};
#endif
