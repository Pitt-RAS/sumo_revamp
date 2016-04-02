#include <Arduino.h>
#include <EncoderMod.h>
#include "config.h"
#include "encoding.h"

Encoder flEn(FL_ENCODERA_PIN, FL_ENCODERB_PIN); //Front Left Encoder (1)
Encoder frEn(FR_ENCODERA_PIN, FR_ENCODERB_PIN); //Front Right Encoder (2)
Encoder blEn(BL_ENCODERA_PIN, BL_ENCODERB_PIN); //Back Left Encoder (3)
Encoder brEn(BR_ENCODERA_PIN, BR_ENCODERB_PIN); //Back Right Encoder (4)

//Returns the value of the selected encoder
float EnRead1(){
		return(flEn.read() * MM_PER_STEP);
}
float EnRead2(){
		return(frEn.read() * MM_PER_STEP);
}
float EnRead3(){
		return(blEn.read() * MM_PER_STEP);
}
float EnRead4(){
		return(brEn.read() * MM_PER_STEP);
}

//Writes value to the selected encoder
void EnWrite1(float new_position){
		flEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}
void EnWrite2(float new_position){
		frEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}
void EnWrite3(float new_position){
		blEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}
void EnWrite4(float new_position){
		brEn.write( (int32_t)rint(new_position / MM_PER_STEP));
}

//Returns veloctiy of selected encoder
float EnVelocity1(){
	 return (1000 * flEn.stepRate() * MM_PER_STEP);
}
float EnVelocity2(){
	 return (1000 * frEn.stepRate() * MM_PER_STEP);
}
float EnVelocity3(){
	 return (1000 * blEn.stepRate() * MM_PER_STEP);
}
float EnVelocity4(){
	 return (1000 * brEn.stepRate() * MM_PER_STEP);
}

//Returns extrapolation of the selected encoder
float EnExtrapolate1(){
	return (flEn.extrapolate() * MM_PER_STEP);
}
float EnExtrapolate2(){
	return (frEn.extrapolate() * MM_PER_STEP);
}
float EnExtrapolate3(){
	return (blEn.extrapolate() * MM_PER_STEP);
}
float EnExtrapolate4(){
	return (brEn.extrapolate() * MM_PER_STEP);
}
