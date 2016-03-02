#ifndef ENCODING_H
#define ENCODING_H

#include <Arduino.h>
#include "config.h"

Encoder flEn(FL_ENCODERA_PIN, FL_ENCODERB_PIN);
Encoder frEn(FR_ENCODERA_PIN, FR_ENCODERB_PIN);
Encoder blEn(BL_ENCODERA_PIN, BL_ENCODERB_PIN);
Encoder brEn(BR_ENCODERA_PIN, BR_ENCODERB_PIN);

//Returns the value of the selected encoder
float EnRead(_int8 encoder){
	if(encoder == 1){
		return(flEn.read()) * MM_PER_STEP)
	}
	else if(encoder == 2){
		return(frEn.read()) * MM_PER_STEP)
	}
	else if(encoder == 3){
		return(blEn.read()) * MM_PER_STEP)
	}
	else if(encoder == 4){
		return(brEn.read()) * MM_PER_STEP)
	}
	else{
		return (.01); //In case error checking was not performed beforehand
	}
}

//Writes value to the selected encoder
void EnWrite(_int8 encoder, float new_position){
	if(encoder == 1){
		flEn.write( (int32_t)rint(new_position / MM_PER_STEP))
	}
	else if(encoder == 2){
		frEn.write( (int32_t)rint(new_position / MM_PER_STEP))
	}
	else if(encoder == 3){
		blEn.write( (int32_t)rint(new_position / MM_PER_STEP))
	}
	else if(encoder == 4){
		brEn.write( (int32_t)rint(new_position / MM_PER_STEP))
	}
	else{
		return (.01); //In case error checking was not performed beforehand
	}
}

float EnVelocity(_int8 encoder){
}

float EnExtrapolate(_int8 encoder){
	
}
