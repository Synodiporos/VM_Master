/*
 * Controller.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include "Controller.h"

Controller::Controller(){

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::activate(){
	if(transceiver){
		transceiver->setActionListener(this);
	}
	if(notification){
		notification->setActiveEnabled(true);
	}
	initialization();
}

void Controller::deactivate(){
	if(transceiver){
		transceiver->setActionListener(nullptr);
	}
	if(notification)
		notification->stopNotify();
}

void Controller::initialization(){

}

void Controller::setNotificationSystem(NotificationSystem* ns){
	this->notification = ns;
}

void Controller::setLoggerSystem(){

}

void Controller::setRFDevice(){

}

void Controller::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){

}

void Controller::actionPerformed(Action action){
	RFTransceiver* radio = (RFTransceiver*)action.getSource();
	uint8_t id = action.getActionId();

	switch(id){
		case RFTransceiver::ON_MESSAGE_RECEIVED:{
			char* msg = (char*)action.getContainer();
			onMessageReceived(msg);
			break;
		}
		case RFTransceiver::ON_MESSAGE_SEND:{
			char* msg = (char*)action.getContainer();
			onMessageSend(msg);
			break;
		}
		case RFTransceiver::ON_CONNECTION_STATE:{
			bool* state = (bool*)action.getContainer();
			onConnectionStateChanged(*state);
			break;
		}
	}
}

void Controller::onMessageReceived(char* msg){
	Serial.print(F("Slave RF Message Received: "));
	Serial.println(msg);

	std::string input = string(msg);
	std::string cmdN;
	vector<string> params;
	AT::parse(input, cmdN, params);

	if(cmdN.compare(ATCMDs::AT_BT)==0){
		char at[RF_PAYLOAD_SIZE];
		char str[] = CMD_ACR;
		sprintf (at, "AT+%s", str);
		RFTransceiver::getInstance()->write(at);
	}
	else if(cmdN.compare(ATCMDs::AT_HV1)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_SR1)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_HV2)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_SR2)==0){

	}


	//CMD* cmd = AT::toCMD(input);
	//cmd->execute();

	/*Serial.print(F("CMD: "));
	Serial.print(input.c_str());
	Serial.print(F(" at= "));
	Serial.println(cmdN.c_str());*/
	//delete cmd;
}

void Controller::onMessageSend(char* msg){

}

void Controller::onConnectionStateChanged(bool state){
	//Serial.print(F("Connection State: "));
	//Serial.println(state);
	this->notification->setConnectionLostEnabled(!state);
}
