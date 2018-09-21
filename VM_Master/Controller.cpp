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
	if(button){
		button->setButtonListener(this);
	}
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
	if(button){
		button->setButtonListener(nullptr);
	}
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
	//requestManager->setEnabled(true);
	//requestManager->startPosting();

	//this->transceiver->startConnectivityCheck();

	//page->reprint();

}

void Controller::setRadioInstance(RF24* radio){
	this->transceiver->initialize(radio);
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
			onRFConnectionStateChanged(*state);
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
		case ST_INITIALIZE_ERROR:{
			Serial.println(F("WIFI INITIALIZING ERROR"));
			break;
		}
		case ST_W_DISCONNECTED:{
			Serial.println(F("WIFI WLAN DISCONNECTED"));
			onWiFiConnectionStateChanged(false);
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
		case ST_W_CONNECTING_FAIL:{
			Serial.println(F("WIFI WLAN CONNECTING FAIL"));
			break;
		}
		case ST_W_CONNECTED:{
			Serial.println(F("WIFI WLAN CONNECTED"));
			onWiFiConnectionStateChanged(true);
			break;
		}
		case ST_S_DISCONNECTED:{
			Serial.println(F("WIFI SERVER DISCONNECTED"));
			break;
		}
		case ST_S_ERROR:{
			Serial.println(F("WIFI SERVER ERROR"));
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
		case ST_P_POSTING_OFF:{
			Serial.println(F("WIFI STOP POSTING"));
			break;
		}

		case ST_P_POSTING_ON:{
			Serial.println(F("WIFI START POSTING"));
			break;
		}
		case ST_P_POSTING_READY:{
			Serial.println(F("WIFI POSTING READY"));
			break;
		}
		case ST_P_POSTING_REQUEST:{
			Serial.println(F("WIFI REQUEST IS POSTING"));
			break;
		}
		case ST_P_SEND_REQUEST:{
			Serial.println(F("WIFI REQUEST SEND"));
			break;
		}
		case ST_P_WAIT_RESP:{
			Serial.println(F("WIFI WAITING REQ RESPONSE"));
			break;
		}
		case ST_P_REQUEST_POSTED:{
			Serial.println(F("WIFI REQUEST POSTED"));
			break;
		}
		case ST_P_REQUEST_POST_ERROR:{
			Serial.println(F("WIFI REQUEST POSTED ERROR"));
			break;
		}
	}
}

void Controller::stateChanged(State state){
	void* source = state.getSource();
	if(source==this->button){
		onButtonStateChanged();
	}
	source = nullptr;
}

void Controller::onMessageReceived(char* msg){
	Serial.print(F("Slave RF Message Received: "));
	Serial.println(msg);

	std::string input = string(msg);
	std::string cmdN;
	vector<string> params;
	AT::parse(input, cmdN, params);

	if(cmdN.compare(ATCMDs::AT_ACK)==0){
		onACKReceived();
	}
	else if(cmdN.compare(ATCMDs::AT_HV1)==0){
		const std::string param = params[0];
		float hv = std::atof(param.c_str())/1000;
		if(this->HV1!=hv){
			this->HV1 = hv;
			onHighVoltage1Changed();
		}
	}
	else if(cmdN.compare(ATCMDs::AT_SR1)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_HV2)==0){
		const std::string param = params[0];
		float hv = std::atof(param.c_str())/1000;
		if(this->HV2!=hv){
			this->HV2 = hv;
			onHighVoltage2Changed();
		}
	}
	else if(cmdN.compare(ATCMDs::AT_SR2)==0){

	}
	else if(cmdN.compare(ATCMDs::AT_BT)==0){
		const std::string param = params[0];
		float btr = std::atof(param.c_str());
		if(this->batteryVoltage!=btr){
			this->batteryVoltage = btr;
			onBatteryVoltageChagned();
		}
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
	Serial.print(F("ON RF MESSAGE SEND: "));
	Serial.println(msg);
}

void Controller::onRFConnectionStateChanged(bool state){
	//Serial.print(F("Connection State: "));
	//Serial.println(state);
	//this->notification->setConnectionLostEnabled(!state);
}

void Controller::onACKReceived(){
	char at[RF_PAYLOAD_SIZE];
	sprintf (at, "AT+%s", CMD_ACR);
	RFTransceiver::getInstance()->write(at);
}

void Controller::onWiFiConnectionStateChanged(bool state){

}

void Controller::onHighVoltage1Changed(){
	//page->setHV10350(this->HV1);
}

void Controller::onHighVoltage2Changed(){
	//page->setHV820(this->HV2);
}

void Controller::onBatteryVoltageChagned(){
	//page->setBatteryLevel(this->batteryVoltage);
}

void Controller::onButtonStateChanged(){
	ButtonState state = button->getButtonState();
	switch(state){
		case ButtonState::CLICKED:{
			//Serial.println(F("CLICKED"));
			break;
		}
		case ButtonState::PRESSED:{
			//Serial.println(F("PRESSED"));
			break;
		}
		case ButtonState::RELEASED:{
			//Serial.println(F("RELEASED"));
			break;
		}
		case ButtonState::HOLDED:{
			//Serial.println(F("HOLDED"));


			char at[RF_PAYLOAD_SIZE];
			sprintf (at, "AT+%s", CMD_ACR);
			RFTransceiver::getInstance()->write(at);

			Serial.print(F("Free RAM BT= "));
			Serial.println(freeMemory(), DEC);
			break;
		}
	}
}

void Controller::validate(){

	transceiver->validate();
	requestManager->validate();
	button->validate();

	if(helper==0 && millis()-time > 5000){
		/*for(int i=0; i<4; i++){
			PostSurgeRequest* req = new PostSurgeRequest(c, c*1000, 0);
			requestManager->pushRequest(req);
			c++;
		}*/
		Serial.println(F("===> PUSH REQUESTS"));

		//HttpRequest* req1 = new TestGetRequest();
		//HttpRequest* req2 = new TestGetRequest();// new PostSurgeRequest(1, 45000, 523);
		//HttpRequest* req3 = new PostBatteryRequest(415, 100, 0);
		//HttpRequest* req4 = new PostSurgeRequest(0, 100000, 2000);
		//HttpRequest* req4 = new PostSurgeRequest(0, 45000, 5000);

		//requestManager->pushRequest(req1);
		//requestManager->pushRequest(req2);
		//requestManager->pushRequest(req3);
		//requestManager->pushRequest(req4);

		for(int i=0; i<4; i++){
			HttpRequest* req1 = new TestGetRequest();
			HttpRequest* req2 = new PostSurgeRequest(1, 10000, 10000);
			HttpRequest* req3 = new PostBatteryRequest(415, 200, 0);
			requestManager->pushRequest(req1);
			requestManager->pushRequest(req2);
			requestManager->pushRequest(req3);
		}

		Serial.print(F("Free RAM AFTER= "));
		Serial.println(freeMemory(), DEC);

		time = millis();
		helper = 1;
	}
	if(helper==1 && millis()-time > 4000){
		//requestManager->startPosting();
		//time = millis();
		helper = 2;
	}
	if(helper==2 && millis()-time > 15000){
		time = millis();
		helper = 2;
	}

}
