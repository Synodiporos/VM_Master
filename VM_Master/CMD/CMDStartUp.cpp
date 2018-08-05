/*
 * CMDStartUp.cpp
 *
 *  Created on: 30 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "CMDStartUp.h"
#include "../System/NotificationSystem.h"

CMDStartUp::CMDStartUp() : CMD(){
	// TODO Auto-generated constructor stub
}

CMDStartUp::~CMDStartUp() {
	// TODO Auto-generated destructor stub
}

std::string CMDStartUp::getName(){
	return "SUP";
}

uint8_t CMDStartUp::onExecute(){
	digitalWrite(LED_WHITE_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);
	digitalWrite(LED_BLUE_PIN, HIGH);
	//tone(BUZZER_PIN, 4000, 250);
	this->time = millis();
	return RES_ONPROGRESS;
}

void CMDStartUp::validate(){
	if(millis() - time > STARTUP_INTERVAL){
		digitalWrite(LED_WHITE_PIN, LOW);
		digitalWrite(LED_RED_PIN, LOW);
		digitalWrite(LED_BLUE_PIN, LOW);
		noTone(BUZZER_PIN);
		NotificationSystem::getInstance()->setActiveEnabled(true);
		CMD::onCompleted();
	}
}
