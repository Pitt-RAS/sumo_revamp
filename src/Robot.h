#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "config.h"
#include "device/ProxSense.h"
#include "device/LineSense.h"
#include <EncoderPittMicromouse.h>

class Robot
{
    private:
        Motion& motion;

        ProxSense frontProx;
        ProxSense rearProx;

        LineSense lineSensors;

        int front_angle;
        int rear_angle;
        int enemy_angle;
        int enemy_direction;

        int desired_direction;
        int desired_velocity;
        int desired_acceleration;

        int current_direction;
        int current_velocity;
        int current_acceleration;

        int current_velocity_FL;
        int current_velocity_FR;
        int current_velocity_BL;
        int current_velocity_BR;

        int desired_velocity_FL;
        int desired_velocity_FR;
        int desired_velocity_BL;
        int desired_velocity_BR;

        int error_FL;
        int error_FR;
        int error_BL;
        int error_BR;

    public:
        Robot(Motion&);

        EncoderPittMicromouse encoderFL;
        EncoderPittMicromouse encoderFR;
        EncoderPittMicromouse encoderBL;
        EncoderPittMicromouse encoderBR;

        float getVelocityFL();
        float getVelocityFR();
        float getVelocityBL();
        float getVelocityBR();

        void update();
        void updateProx();
        void updateLine();
        void updateEncoders();


        int getEnemyAngle();
        int getEnemyDirection();
        bool enemy_in_sight;

        int getLineDirection();
        bool lineInDirection();
        bool is_white_FL;
        bool is_white_FR;
        bool is_white_BL;
        bool is_white_BR;
        bool is_white_F;
        bool is_white_B;
        bool is_white_L;
        bool is_white_R;
        bool on_line;

        int getCurrentVelocity();

        // bool possiblyInContact();
        bool possiblyLosing();
        bool possiblyUnder();
        // bool wheelsLostTraction();
}


