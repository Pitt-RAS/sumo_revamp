#ifndef LINE_H 
#define LINE_H

#include <Arduino.h>
#include "../../config.h"

class Line
{
	private:
	    int FL_PIN;
        int FR_PIN;
        int BL_PIN;
        int BR_PIN;

        bool is_white[3][3];

    public: 
        Line(int fl_pin, int fr_pin, int bl_pin, int br_pin) :
                  FL_PIN(fl_pin),
                  FR_PIN(fr_pin),
                  BL_PIN(bl_pin),
                  BR_PIN(br_pin) {
              pinMode(FL_PIN, INPUT);
              pinMode(FR_PIN, INPUT);
              pinMode(BL_PIN, INPUT);
              pinMode(BR_PIN, INPUT);
              
              update();
        }
    
        void update();

        bool isWhite(int, int);
};
#endif
