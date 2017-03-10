#ifndef PROXSENSE_H
#define PROXSENSE_H

#include <Arduino.h>
#include "../../config.h"

class ProxSense
{
    private:
        bool prox[5];
        int *pin_array;
        int *weight_array;
        
    public:
        ProxSense(int *pin_array_input, int *weight_array_input) :
          pin_array(pin_array_input), 
          weight_array(weight_array_input)
        {
            for (int pin_iter = 0; pin_iter < 5; pin_iter++) {
                pinMode(pin_array[pin_iter], INPUT);    
            }
        }

        void update();
        int generateAngle();
        bool sensorHigh();
        int readAngle();
 };
 
 #endif
