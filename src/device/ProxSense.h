#ifndef PROXSENSE_H
#define PROXSENSE_H

class ProxSense
{
    private:
        bool prox[5];
        int *prox_pin;
        int *prox_weight;
        
    public:
        ProxSense(int *prox_pin_input, int *prox_weight_input) :
            prox_pin(prox_pin_input), prox_weight(prox_weight_input) {}

        void update();
        int generateAngle();
        bool sensorHigh();
        int readAngle();
 };
 
 #endif
