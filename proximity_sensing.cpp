#include <Arduino.h>
#include <ctsdint.h>
#include "config.h"
#include "proximity_sensing.h"
#include "digitalReadFast.h"

uint8_t checkFrontProx(){
	bool prox1;
	bool prox2;
	bool prox3;
	bool prox4;
	bool prox5;
	
	prox1 = digitalReadFast(F_PROX1_PIN);
	prox2 = digitalReadFast(F_PROX2_PIN;
	prox3 = digitalReadFast(F_PROX3_PIN);
	prox4 = digitalReadFast(F_PROX4_PIN);
	prox5 = digitalReadFast(F_PROX5_PIN);
	
	//Take Logic From Last year
	if(prox1){
		
	}
}

uint8_t checkBackProx(){
	prox6 = digitalReadFast(R_PROX1_PIN);	
	prox7 = digitalReadFast(R_PROX2_PIN);
	prox8 = digitalReadFast(R_PROX3_PIN);
	prox9 = digitalReadFast(R_PROX4_PIN);
	prox10 = digitalReadFast(R_PROX5_PIN);
	
	//Take logic from last year
	if(prox6){
		
	})
}
