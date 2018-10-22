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

void NotificationSystem::validate(){

}
