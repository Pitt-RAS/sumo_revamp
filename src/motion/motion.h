#ifndef MOTION_H
#define MOTION_H

#include <Arduino.h>
#include <EncoderPittMicromouse.h>

#include "PIDController.h"

#include "../config.h"
#include "../device/motors.h"
#include "../device/LineSense.h"
#include "../FSM/Enemy.h"


class Motion
{
    private:

        Enemy& opponent;
        LineSense& lineSensors;

        Motor motor_l;
        Motor motor_r;

        PIDController pid_left;
        PIDController pid_right;

        EncoderPittMicromouse flEn; //Front Left EncoderPittMicromouse (1)
        EncoderPittMicromouse frEn; //Front Right EncoderPittMicromouse (2)
        EncoderPittMicromouse blEn; //Back Left EncoderPittMicromouse (3)
        EncoderPittMicromouse brEn; //Back Right EncoderPittMicromouse (4)

        float target_left_v, target_right_v;
        //Private motion functions
        void setVelRaw(int pwmr, int pwml);

    public:
        Motion(Enemy& opponentInput, LineSense& lineSensorsInput) :
            opponent(opponentInput),
            lineSensors(lineSensorsInput),
            motor_l (L_MOTOR_DIR_PIN, L_MOTOR_PWM_PIN, L_MOTOR_FORWARD_STATE),
            motor_r (R_MOTOR_DIR_PIN, R_MOTOR_PWM_PIN, R_MOTOR_FORWARD_STATE),
            pid_left (KP_POSITION, KI_POSITION, KD_POSITION),
            pid_right (KP_POSITION, KI_POSITION, KD_POSITION),
            flEn(FL_ENCODERA_PIN, FL_ENCODERB_PIN),   //Front Left Encoder (1)
            frEn(FR_ENCODERA_PIN, FR_ENCODERB_PIN),   //Front Right Encoder (2)
            blEn(BL_ENCODERA_PIN, BL_ENCODERB_PIN),   //Back Left Encoder (3)
            brEn(BR_ENCODERA_PIN, BR_ENCODERB_PIN),   //Back Right Encoder (4)
            target_left_v(0),
            target_right_v(0) {}
            

        void setVel(float v, float w);
        void setVel(float v);
        void charge();
        void search();
        void deployRamps();
        void guardLine();

        int getCurrentDirection();

        //Must be called a set rate
        void update();

        //Returns veloctiy of selected EncoderPittMicromouse
        float EnVelocityFL();
        float EnVelocityFR();
        float EnVelocityBL();
        float EnVelocityBR();

 };

#endif
