#include <Arduino.h>
#include <EncoderMod.h>
#include "config.h"
#include "encoding.h"

Encoder flEn(FL_ENCODERA_PIN, FL_ENCODERB_PIN); //Front Left Encoder (1)
Encoder frEn(FR_ENCODERA_PIN, FR_ENCODERB_PIN); //Front Right Encoder (2)
Encoder blEn(BL_ENCODERA_PIN, BL_ENCODERB_PIN); //Back Left Encoder (3)
Encoder brEn(BR_ENCODERA_PIN, BR_ENCODERB_PIN); //Back Right Encoder (4)

//Returns the value of the selected encoder
float EnReadFL(){
		return(flEn.read() * MM_PER_STEP);
}
float EnReadFR(){
		return(frEn.read() * MM_PER_STEP);
}
float EnReadBL(){
		return(blEn.read() * MM_PER_STEP);
}
float EnReadBR(){
		return(brEn.read() * MM_PER_STEP);
}

//Writes value to the selected encoder
void EnWriteFL(float new_position){
		flEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}
void EnWriteFR(float new_position){
		frEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}
void EnWriteBL(float new_position){
		blEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}
void EnWriteBR(float new_position){
		brEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}

//Returns veloctiy of selected encoder
float EnVelocityFL(){
	 return (1000 * flEn.stepRate() * MM_PER_STEP);
}
float EnVelocityFR(){
	 return (1000 * frEn.stepRate() * MM_PER_STEP);
}
float EnVelocityBL(){
	 return (1000 * blEn.stepRate() * MM_PER_STEP);
}
float EnVelocityBR(){
	 return (1000 * brEn.stepRate() * MM_PER_STEP);
}

//Returns extrapolation of the selected encoder
float EnExtrapolateFL(){
	return (flEn.extrapolate() * MM_PER_STEP);
}
float EnExtrapolateFR(){
	return (frEn.extrapolate() * MM_PER_STEP);
}
float EnExtrapolateBL(){
	return (blEn.extrapolate() * MM_PER_STEP);
}
float EnExtrapolateBR(){
	return (brEn.extrapolate() * MM_PER_STEP);
}
