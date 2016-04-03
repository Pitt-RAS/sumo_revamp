#include <Arduino.h>
#include "config.h"
#include "sensors_line.h"

//We need functions to initialize the interrupts for the line sensor pins
//Respond to interrupts and set the appropriate flags
//The idea is to do this like the encoder library where each sensor has its own function that can be called