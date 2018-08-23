/*
 * Controller.cpp
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#include "Controller.h"

Controller::Controller(){
	//initialization();
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
}

void Controller::deactivate(){
	if(transceiver){
		transceiver->setActionListener(nullptr);
	}
	if(notification)
		notification->stopNotify();
}

void Controller::initialization(){
	page->reprint();
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

	if(radio==this->transceiver)
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
	//Serial.print(F("Slave RF Message Received: "));
	//Serial.println(msg);

	std::string input = string(msg);
	std::string cmdN;
	vector<string> params;
	AT::parse(input, cmdN, params);

	if(cmdN.compare(ATCMDs::AT_ACK)==0){
		char at[RF_PAYLOAD_SIZE];
		char str[] = CMD_ACR;
		sprintf (at, "AT+%s", str);
		RFTransceiver::getInstance()->write(at);
	}
	else if(cmdN.compare(ATCMDs::AT_HV1)==0){
		const std::string param = params[0];
		float hv = std::atof(param.c_str())/1000;
		page->setHV10350(hv);
	}
	else if(cmdN.compare(ATCMDs::AT_SR1)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_HV2)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_SR2)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_BT)==0){
		const std::string param = params[0];
		float hv = std::atof(param.c_str());
		page->setBatteryLevel(hv);
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
