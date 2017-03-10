#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include <EncoderPittMicromouse.h>

#include "PIDController.h"

#include "../config.h"
#include "../device/motors.h"
#include "../Robot.h"


class Motion
{
    private:
        Robot& sumo;

        EncoderPittMicromouse encoderFL;
        EncoderPittMicromouse encoderFR;
        EncoderPittMicromouse encoderBL;
        EncoderPittMicromouse encoderBR;

        Motor motorLeft;
        Motor motorRight;

        PIDController pidLeft;
        PIDController pidRight;

        float desired_velocity_left;
        float desired_velocity_right;
        float desired_velocity_net;

        float current_velocity_left;
        float current_velocity_right;
        float current_velocity_net;

        void setVelRaw(float modified_velocity, float modified_velocity);

    public:
        Motion(Robot&);

        void setVel(float, float);
        void setVel(float);
        void charge();
        void search();
        void deployRamps();
        void guardLine();

        float getDesiredVelocityLeft();
        float getDesiredVelocityRight();
 };

#endif
