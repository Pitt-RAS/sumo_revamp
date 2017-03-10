#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <Arduino.h>
#include "../config.h"

class PIDController {
    private:
        float i_term = 0;
        elapsedMicros elapsed_time;
        float last_value = NAN;
        float kp, ki, kd;
        float i_lower_bound, i_upper_bound;
    public:
        PIDController(float inital_KP, float initial_KI, float initial_KD, float initial_i_upper_bound,
                      float initial_i_lower_bound);
        
        float Calculate(float current_value, float target_value);
    };

#endif
