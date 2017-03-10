#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>

#include "../config.h"
#include "../robot/Robot.h"
#include "motors.h"
#include "PIDController.h"


class Motion
{
    private:
        Robot& sumo;

        Motor motorLeft;
        Motor motorRight;

        PIDController pidLeft;
        PIDController pidRight;

        float desired_velocity_net;
        float desired_velocity_left;
        float desired_velocity_right;

        float current_velocity_net;
        float current_velocity_left;
        float current_velocity_right;

        void setVelRaw(float, float);

    public:
        Motion(Robot& passedSumo) :
            sumo(passedSumo),
            motorLeft (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE),
            motorRight (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE),
            pidLeft  (KP_POSITION, KI_POSITION, KD_POSITION, 10000, 0),
            pidRight (KP_POSITION, KI_POSITION, KD_POSITION, 10000, 0) {

                desired_velocity_net = 0;
                desired_velocity_left = 0;
                desired_velocity_right = 0;
            }

        void update();
        void setVel(float, float);
        void setVel(float);
        void charge();
        void search();
        void deployRamps();
        void guardLine();
        void testVel(float);
 };

#endif
