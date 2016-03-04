#include <Arduino.h>
#include <ctsdint.h>
#include "config.h"
#include "proximity_sensing.h"

uint8_t checkFrontProx(){
	bool prox1;
	bool prox2;
	bool prox3;
	bool prox4;
	bool prox5;
	uint8_t error;
	
	proxSense1 = digitalRead(F_PROX1_PIN);
	proxSense2 = digitalRead(F_PROX2_PIN;
	proxSense3 = digitalRead(F_PROX3_PIN);
	proxSense4 = digitalRead(F_PROX4_PIN);
	proxSense5 = digitalRead(F_PROX5_PIN);
	
	 //Take logic from last year for front sensors
	 // if front sensors see something, calculate PID values
    if ((proxSense1 && proxSense2 && proxSense3 && proxSense4 && proxSense5) == 0)
    {
      // calculate offset "error" from center
      if  (!proxSense1 && proxSense2 && proxSense3 && proxSense4 && proxSense5)
      {
        error = -4;
      }
      else if (proxSense1 && proxSense2 && proxSense3 && proxSense4 && !proxSense5)
      {
        error = 4;
      }
      else if (!proxSense1 && !proxSense2 && proxSense3 && proxSense4 && proxSense5)
      {
        error = -3;
      }
      else if (proxSense1 && proxSense2 && proxSense3 && !proxSense4 && !proxSense5)
      {
        error = 3;
      }
      else if ((proxSense1 && !proxSense2 && proxSense3 && proxSense4 && proxSense5) || (!proxSense1 && !proxSense3 && proxSense4 && proxSense5))
      {
        error = -2;
      }
      else if ((proxSense1 && proxSense2 && proxSense3 && !proxSense4 && proxSense5) || (proxSense1 && proxSense2 && !proxSense3 && !proxSense5))
      {
        error = 2;
      }
      else if ((proxSense1 && !proxSense2 && !proxSense3 && proxSense4 && proxSense5) || (!proxSense1 && !proxSense4 && proxSense5))
      {
        error = -1;
      }
      else if ((proxSense1 && proxSense2 && !proxSense3 && !proxSense4 && proxSense5) || (proxSense1 && !proxSense2 && !proxSense5))
      {
        error = 1;
      }
      else
      {
        error = 0;
      }
      return error;
}

uint8_t checkBackProx(){
	proxSense6 = digitalRead(R_PROX1_PIN);	
	proxSense7 = digitalRead(R_PROX2_PIN);
	proxSense8 = digitalRead(R_PROX3_PIN);
	proxSense9 = digitalRead(R_PROX4_PIN);
	proxSense10 = digitalRead(R_PROX5_PIN);
	uint8_t error;
	
	      // calculate offset "error" from center
      if  (!proxSense6 && proxSense7 && proxSense8 && proxSense9 && proxSense10)
      {
        error = 4;
      }
      else if (proxSense6 && proxSense7 && proxSense8 && proxSense9 && !proxSense10)
      {
        error = -4;
      }
      else if (!proxSense6 && !proxSense7 && proxSense8 && proxSense9 && proxSense10)
      {
        error = 3;
      }
      else if (proxSense6 && proxSense7 && proxSense8 && !proxSense9 && !proxSense10)
      {
        error = -3;
      }
      else if ((proxSense6 && !proxSense7 && proxSense8 && proxSense9 && proxSense10) || (!proxSense6 && !proxSense8 && proxSense9 && proxSense10))
      {
        error = 2;
      }
      else if ((proxSense6 && proxSense7 && proxSense8 && !proxSense9 && proxSense10) || (proxSense6 && proxSense7 && !proxSense8 && !proxSense10))
      {
        error = -2;
      }
      else if ((proxSense6 && !proxSense7 && !proxSense8 && proxSense9 && proxSense10) || (!proxSense6 && !proxSense9 && proxSense10))
      {
        error = 1;
      }
      else if ((proxSense6 && proxSense7 && !proxSense8 && !proxSense9 && proxSense10) || (proxSense6 && !proxSense7 && !proxSense10))
      {
        error = -1;
      }
      else
      {
        error = 0;
      }
	return error;
}
