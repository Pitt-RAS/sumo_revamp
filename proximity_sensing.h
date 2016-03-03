#ifndef PROXIMITY_SENSING_H
#define PROXIMITY_SENSING_H

#include <Arduino.h>
#include <cstdint.h>
#include ""config.h"

extern bool prox1;
extern bool prox2;
extern bool prox3;
extern bool prox4;
extern bool prox5;
extern bool prox6;
extern bool prox7;
extern bool prox8;
extern bool prox9;
extern bool prox10;

uint8_t checkFrontProx();
uint8_t checkBackProx();

#endif
