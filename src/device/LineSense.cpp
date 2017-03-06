#include <Arduino.h>
#include "../config.h"
#include "LineSense.h"

LineSense::LineSense(int fl_pin, int fr_pin, int bl_pin, int br_pin){
	FL_PIN = fl_pin;
	FR_PIN = fr_pin;
	BL_PIN = bl_pin;
	BR_PIN = br_pin;
 	  
	pinMode(FR_PIN, INPUT);
	pinMode(FL_PIN, INPUT);
	pinMode(BL_PIN, INPUT);
	pinMode(BR_PIN, INPUT);
	
	update();
}

void LineSense::update() {
      isWhiteFL = !digitalRead(FL_PIN);
      isWhiteFR = !digitalRead(FR_PIN);
      isWhiteBL = !digitalRead(BL_PIN);
      isWhiteBR = !digitalRead(BR_PIN);
}
