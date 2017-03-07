#ifndef PROXSENSE_H
#define PROXSENSE_H

class ProxSense
{
    private:
        bool prox[5];
        int *pin_array;
        int *weight_array;
        
    public:
        ProxSense(int *pin_array_input, int *weight_array_input) :
            prox_pin(prox_pin_input), 
            prox_weight(prox_weight_input) {}

        void update();
        int generateAngle();
        bool sensorHigh();
        int readAngle();
 };
 
 #endif
