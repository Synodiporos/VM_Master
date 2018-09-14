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
	if(requestManager){
		requestManager->setActionListener(this);
	}
	//if(notification){
	//	notification->setActiveEnabled(true);
	//}
}

void Controller::deactivate(){
	if(transceiver){
		transceiver->setActionListener(nullptr);
	}
	if(requestManager){
		requestManager->setActionListener(nullptr);
	}
	//if(notification)
	//	notification->stopNotify();
}

void Controller::initialization(){
	requestManager->setEnabled(true);
	requestManager->startPosting();

	//page->reprint();
}

void Controller::setNotificationSystem(NotificationSystem* ns){
	//this->notification = ns;
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
	void* source = action.getSource();
	uint8_t id = action.getActionId();

	if(source==this->transceiver)
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

	if(source==this->requestManager)
	switch(id){
		case ST_OFF:{
			Serial.println(F("WIFI OFF"));
			break;
		}
		case ST_BLUGED:{
			Serial.println(F("WIFI BLUDED"));
			break;
		}
		case ST_INITIALIZING:{
			Serial.println(F("WIFI INITIALIZING"));
			break;
		}
		case ST_INITIALIZED:{
			Serial.println(F("WIFI INITIALIZED"));
			break;
		}
		case ST_W_DISCONNECTED:{
			Serial.println(F("WIFI WLAN DISCONNECTED"));
			break;
		}
		case ST_W_CHECK:{
			Serial.println(F("WIFI WLAN CHECK"));
			break;
		}
		case ST_W_CONNECTING:{
			Serial.println(F("WIFI WLAN CONNECTING"));
			break;
		}
		case ST_W_CONNECTED:{
			Serial.println(F("WIFI WLAN CONNECTED"));
			break;
		}
		case ST_S_DISCONNECTED:{
			Serial.println(F("WIFI WLAN DISCONNECTED"));
			break;
		}
		case ST_S_CHECK:{
			Serial.println(F("WIFI SERVER CHECK"));
			break;
		}
		case ST_S_CONNECTING:{
			Serial.println(F("WIFI SERVER CONNECTING"));
			break;
		}
		case ST_S_CONNECTED:{
			Serial.println(F("WIFI SERVER CONNECTED"));
			break;
		}
		case ST_P_STOP_POSTING:{
			Serial.println(F("WIFI STOP POSTING"));
			break;
		}
		case ST_P_POSTING:{
			Serial.println(F("WIFI START POSTING"));
			break;
		}
		case ST_P_POST_REQUEST:{
			Serial.println(F("WIFI POST REQUEST"));
			break;
		}
		case ST_P_SEND_REQUEST:{
			Serial.println(F("WIFI SEND REQUEST"));
			break;
		}
	}

	Serial.print(F("$ Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);
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
	//this->notification->setConnectionLostEnabled(!state);
}
