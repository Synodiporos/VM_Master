/*
 * CMDTestLeds.cpp
 *
 *  Created on: 28 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "CMDTestLeds.h"

CMDTestLeds::CMDTestLeds() {
	// TODO Auto-generated constructor stub

}

CMDTestLeds::~CMDTestLeds() {
	// TODO Auto-generated destructor stub
}

string CMDTestLeds::getName(){
	return "TLS";
}

uint8_t CMDTestLeds::onExecute(){
	string param = getParams()[0];
	this->time = millis();
	if(param.compare("w")){
		led = LED_WHITE_PIN;
		digitalWrite(led, HIGH);
	}
	else if(param.compare("r")){
		led = LED_RED_PIN;
		digitalWrite(led, HIGH);
	}
	else if(param.compare("g")){
		led = LED_BLUE_PIN;
		digitalWrite(led, HIGH);
	}
	else if(param.compare("a")){
		led = 255;
		digitalWrite(LED_WHITE_PIN, HIGH);
		digitalWrite(LED_RED_PIN, HIGH);
		digitalWrite(LED_BLUE_PIN, HIGH);
	}
	else{
		return RES_WRONGPARAMS;
	}
	return RES_ONPROGRESS;
}

void CMDTestLeds::validate(){
	CMD::validate();
	if(millis()-this->time > TEST_INTERVAL){
		if(led==255){
			digitalWrite(LED_WHITE_PIN, LOW);
			digitalWrite(LED_RED_PIN, LOW);
			digitalWrite(LED_BLUE_PIN, LOW);
		}
		else
			digitalWrite(LED_BLUE_PIN, LOW);
		CMD::onCompleted();
	}
}
