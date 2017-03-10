#include "PIDController.h"

PIDController::PIDController(float initial_KP, float initial_KI, float initial_KD, float initial_i_upper_bound,
                             float initial_i_lower_bound) {
    kp = initial_KP;
    ki = initial_KI;
    kd = initial_KD;
  
    if (initial_i_lower_bound == 0) {
        initial_i_lower_bound = -initial_i_upper_bound;
    }

    i_lower_bound = initial_i_lower_bound;
    i_upper_bound = initial_i_upper_bound;
}

float PIDController::Calculate(float current_value, float target_value) {
    float error = current_value - target_value;

    i_term += ki * error * elapsed_time;
    i_term = constrain(i_term, i_lower_bound, i_upper_bound);

    if (isnan(last_value)) {
        last_value = current_value;
    }


    float output = -kp * error - i_term + kd * (-current_value + last_value) / elapsed_time;
    last_value = current_value;
    elapsed_time = 0;

    return output;
}
