/*
 * NotificationSystem.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */
#include "Arduino.h"
#include "NotificationSystem.h"

NotificationSystem* NotificationSystem::instance = nullptr;

NotificationSystem::NotificationSystem(){
	initialize();
}

NotificationSystem::~NotificationSystem() {
	// TODO Auto-generated destructor stub
}

NotificationSystem* NotificationSystem::getInstance(){
	if(instance==nullptr){
		instance = new NotificationSystem();
	}
	return instance;
}

void NotificationSystem::initialize(){

}

void NotificationSystem::setHVWarningEnabled(bool enabled){
	if(isHVWarningEnabled()==enabled)
		return;
	Serial.println(F( " setHVWarningEnabled "));
	if(enabled){
		state |= HV_WARNING;
		Serial.println(F( " - Enabled HV"));

		ledRed.stop();
		ledRed.setHeadTone(LED_M5);
		ledRed.play();
	}
	else{
		state &= 255-HV_WARNING;
		Serial.println(F( " - Disable RED"));
		ledRed.stop();

		if(isActiveEnabled()){
			ledWhite.stop();
			ledWhite.setHeadTone(LED_M1);
			ledWhite.play();
		}else{
			ledWhite.stop();
		}

		if(isBatterLowEnabled()){
			Serial.println(F( " - Enable Battery"));
			ledRed.stop();
			ledRed.setHeadTone(LED_M6);
			ledRed.play();
		}
	}
	onStateChanged(HV_WARNING);
}

void NotificationSystem::setBatteryLowEnabled(bool enabled){
	if(isBatterLowEnabled()==enabled)
			return;
	Serial.println( " setBatteryLowEnabled ");
	if(enabled){
		state |= BATTERY;
		if(!isHVWarningEnabled()){
			Serial.println(F( " - Enable Battery"));
			ledRed.stop();
			ledRed.setHeadTone(LED_M6);
			ledRed.play();
		}
	}
	else{
		state &= 255-BATTERY;
		if(!isHVWarningEnabled()){
			Serial.println(F( " - Disable RED"));
			ledRed.stop();
			if(isErrorEnabled()){
				Serial.println(F( " - Enable Error"));
				ledRed.stop();
				ledRed.setHeadTone(LED_M7);
				ledRed.play();
			}
		}
	}
	onStateChanged(BATTERY);
}

void NotificationSystem::setErrorEnabled(bool enabled){
	if(isErrorEnabled()==enabled)
			return;
	Serial.println( " setErrorEnabled ");
	if(enabled){
		state |= ERROR;
		if(!isHVWarningEnabled()){
			if(!isBatterLowEnabled()){
				Serial.println(F(" - Enable Error"));
				ledRed.stop();
				ledRed.setHeadTone(LED_M7);
				ledRed.play();
			}
		}
	}
	else{
		state &= 255-ERROR;
		if(!isHVWarningEnabled()){
			if(!isBatterLowEnabled()){
				Serial.println(F( " - Disable RED"));
				ledRed.stop();
			}
		}
	}
	onStateChanged(ERROR);
}

void NotificationSystem::setActiveEnabled(bool enabled){
	if(isActiveEnabled()==enabled)
		return;
	if(enabled){
		state |= ACTIVE;
		if(!isHVWarningEnabled()){
			ledWhite.stop();
			ledWhite.setHeadTone(LED_M1);
			ledWhite.play();
		}
	}
	else{
		state &= 255-ACTIVE;
		if(!isHVWarningEnabled()){
			ledWhite.stop();
		}
	}
	onStateChanged(ACTIVE);
}

void NotificationSystem::setConnectionLostEnabled(bool enabled){
	if(enabled){
		state |= CONNECTION_LOST;
	}
	else{
		state &= 255-CONNECTION_LOST;
	}
}

void NotificationSystem::setTranferDataEnabled(bool enabled){
	if(enabled){
		state |= TRANSFER;
	}
	else{
		state &= 255-TRANSFER;
	}
}

bool NotificationSystem::isHVWarningEnabled(){
	return bitRead(state, 7) == 1;
}

bool NotificationSystem::isBatterLowEnabled(){
	return bitRead(state, 6) == 1;
}

bool NotificationSystem::isErrorEnabled(){
	return bitRead(state, 5) == 1;
}

bool NotificationSystem::isConnectionLostEnabled(){
	return bitRead(state, 4) == 1;
}

bool NotificationSystem::isTranferDataEnabled(){
	return bitRead(state, 3) == 1;
}

bool NotificationSystem::isActiveEnabled(){
	return bitRead(state, 2) == 1;
}

void NotificationSystem::onStateChanged(byte change){
	if(change>=32){
		//Serial.println("RED change");
		if(change>=state){

		}
	}
	else if(change>=8){
		Serial.println(F("BLUE change"));
		byte state = this->state || 11100000;
		if(change>=state){

		}
	}
	else if(change>=4){
		Serial.println(F("WHITE change"));
		byte state = this->state || 11111000;
		if(change>=state){

		}
	}
}

void NotificationSystem::stopNotify(){
	ledWhite.stop();
	ledRed.stop();
	ledBlue.stop();
}

void NotificationSystem::validate(){
	ledWhite.validate();
	ledRed.validate();
	ledBlue.validate();
}
