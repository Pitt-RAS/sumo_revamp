#ifndef SUMO_SENSORS_LINE_H_
#define SUMO_SENSORS_LINE_H_

#include "../config.h"
#include <Arduino.h>

class LineSensor
{
	private:
	  int FL_PIN;
      int FR_PIN;
      int BL_PIN;
      int BR_PIN;
    public: 
        LineSensor(int fl_pin, int fr_pin, int bl_pin, int br_pin);
    
        void update();
           
        bool isWhiteFL;
        bool isWhiteFR;
        bool isWhiteBL;
        bool isWhiteBR;
};


#endif