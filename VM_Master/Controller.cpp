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
		button->setActionListener(this);
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
		button->setActionListener(nullptr);
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
	//requestBuffer->initialize();

	transceiver->powerUp();
	transceiver->initialize();
	transceiver->startListening();
	transceiver->setEnabled(true);

	requestManager->setEnabled(true);
	requestManager->startPosting();

	//this->transceiver->startConnectivityCheck();

	//page->reprint();

}

/*void Controller::propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery){

}*/

void Controller::actionPerformed(Action action){
	void* source = action.source;
	uint8_t id = action.actionId;

	if(source==this->transceiver)
	switch(id){
		case RFTransceiver::ON_CONNECTION_STATE:{
			bool* state = (bool*)action.container;
			onRFConnectionStateChanged(*state);
			break;
		}
		case RFTransceiver::ON_MESSAGE_RECEIVED:{
			char* msg = (char*)action.container;
			onRFMessageReceived(msg);
			break;
		}
		case RFTransceiver::ON_MESSAGE_SEND:{
			char* msg = (char*)action.container;
			onRFMessageSend(msg);
			break;
		}
	}

	if(source==this->requestManager){
		Serial.println(id);
		bool wifiConnected = id >= ST_W_CONNECTED;
		if(this->wifiConnected!=wifiConnected){
			this->wifiConnected = wifiConnected;
			onWiFiConnectionStateChanged(this->wifiConnected);
		}
		if(id==ST_P_RESPONSE_COMPLETED){
			onWifiHttpResponseReceived(
					*this->requestManager->httpRequest,
					this->requestManager->httpResponse);
		}
	}
	/*switch(id){
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
	}*/

	if(source==this->button){
		onButtonStateChanged();
	}
	source = nullptr;
}

void Controller::onRFMessageReceived(char* msg){
	Serial.print(F("ON MSR: "));
	Serial.println(msg);

	/*std::string input = string(msg);
	std::string cmdN;
	vector<string> params;
	AT::parse(input, cmdN, params);*/

	uint8_t id;
	String cmd;
	char params[3][8] = {'\0', '\0', '\0'};
	uint8_t res = CharUtil::parse(msg, cmd, id, params);

	if(cmd.compareTo(CMD_ACK)==0){
		//onACKReceived();
		/*char at[RF_PAYLOAD_SIZE];
		params[1][0] = '\0';
		CharUtil::compineAT(at, CMD_ACR, id, params);
		RFTransceiver::getInstance()->write(at);*/
	}
	else if(cmd.compareTo(CMD_HV1)==0){
		float hv = (float)std::atof(params[0])/1000;
		if(this->HV1!=hv){
			this->HV1 = hv;
			onHighVoltage1Changed();
		}
	}
	else if(cmd.compareTo(CMD_SR1)==0){
		uint32_t charge = std::atof(params[0]);
		uint16_t slope = std::atof(params[1]);
		uint32_t datetime = std::atof(params[2]);
		Surge surge ;
		surge.device = 1;
		surge.charge = charge;
		surge.slope = slope;
		surge.datetime = datetime;
		onRFSurgeRequestReceived(surge);
	}
	else if(cmd.compareTo(CMD_HV2)==0){
		float hv = (float)std::atof(params[0])/1000;
		if(this->HV2!=hv){
			this->HV2 = hv;
			onHighVoltage2Changed();
		}
	}
	else if(cmd.compareTo(CMD_SR2)==0){
		uint32_t charge = std::atof(params[0]);
		uint16_t slope = std::atof(params[1]);
		uint32_t datetime = std::atof(params[2]);
		Surge surge ;
		surge.device = 2;
		surge.charge = charge;
		surge.slope = slope;
		surge.datetime = datetime;
		onRFSurgeRequestReceived(surge);
	}
	else if(cmd.compareTo(CMD_BAT)==0){
		float btr = (float)(std::atof(params[0])/100);
		if(this->batteryVoltage!=btr){
			this->batteryVoltage = btr;
			onBatteryVoltageChagned();
		}
		uint16_t voltage = std::atof(params[0]);
		uint8_t percentage = std::atof(params[1]);
		uint8_t alarm = std::atof(params[2]);
		PostBatteryRequest req(voltage, percentage, alarm);
		//this->requestManager->pushRequest(&req);
	}

	if(id>0){
		char at[RF_PAYLOAD_SIZE];
		params[0][0] = '\0';
		params[1][0] = '\0';
		params[2][0] = '\0';
		CharUtil::compineAT(at, CMD_ACR, id, params);
		RFTransceiver::getInstance()->write(at);
	}
}

void Controller::onRFMessageSend(char* msg){
	Serial.print(F("ON MSS: "));
	Serial.println(msg);
}

void Controller::onRFSurgeRequestReceived(Surge surge){
	//this->requestBuffer->push(surge);
}

void Controller::onRFConnectionStateChanged(bool state){
	//Serial.print(F("Connection State: "));
	//Serial.println(state);
	//this->notification->setConnectionLostEnabled(!state);
}
/*
void Controller::onACKReceived(){
	char at[RF_PAYLOAD_SIZE];
	uint8_t id = 254;
	char params[3][8] = {'\0','\0','\0'};
	CharUtil::compineAT(at, CMD_ACR, id, params);
	sprintf (at, at, CMD_ACR);
	RFTransceiver::getInstance()->write(at);
}*/

void Controller::onWiFiConnectionStateChanged(bool state){
	digitalWrite(LED_WHITE_PIN, state);
}

void Controller::onWifiHttpResponseReceived(
			HttpRequest& request, HttpResponse& response){
	uint8_t l = response.getLenght()-1;
	char cont[l];
	for(int i=1; i<l; i++){
		cont[i-1] = response.getContent()[i];
	}
	cont[l-1] = '\0';

	uint8_t type = request.getRequestType();
	switch(type){
		case REQUEST_TYPE_SURGE :{
			break;
		}
		case REQUEST_TYPE_BATTERY :{
			break;
		}
		case REQUEST_TYPE_INFO :{
			unsigned long int dt = atol(cont);
			if(dt>0)
				UnixTime::setUnixTime(dt+2);
			break;
		}
		case REQUEST_TYPE_DATETIME :{
			unsigned long int dt = atol(cont);
			if(dt>0)
				UnixTime::setUnixTime(dt+2);
			break;
		}
	}
}

void Controller::onHighVoltage1Changed(){
	onHVWarningStateChanged();
	page->setHV10350(this->HV1);
}

void Controller::onHighVoltage2Changed(){
	onHVWarningStateChanged();
	page->setHV820(this->HV2);
}

void Controller::onHVWarningStateChanged(){
	bool state = HV1>3 || HV2>3;
	if(HVWARNING!=state){
		HVWARNING = state;
		if(HVWARNING){

		}
	}
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
			//Serial.print(F("BUFFER size: "));
			//Serial.println(requestBuffer->getSize());
			Serial.print(F("Unix: "));
			Serial.println(UnixTime::getUnixTime());

			Serial.print(F("RAM= "));
			Serial.println(freeMemory(), DEC);
			break;
		}
		case ButtonState::RELEASED:{
			//Serial.println(F("RELEASED"));
			break;
		}
		case ButtonState::HOLDED:{
			//requestBuffer->clear();
			//Serial.print(F("BUFFER size: "));
			//Serial.println(requestBuffer->getSize());
			GetInfoRequest* req = new GetInfoRequest(254);
			PostBatteryRequest* req2 = new PostBatteryRequest(411, 92, 0);

			//char buffer[REQUEST_URL_PARAMS_LENGHT];
			//req.createRequestContent(buffer);
			this->requestManager->pushRequest(req);
			Serial.println(F("->"));

			break;
		}
	}
}

void Controller::validate(){
	transceiver->validate();
	requestManager->validate();
	button->validate();
	notification->validate();

	if(helper==0 && millis()-time > 5000){
		/*for(int i=0; i<4; i++){
			PostSurgeRequest* req = new PostSurgeRequest(c, c*1000, 0);
			requestManager->pushRequest(req);
			c++;
		}*/
		//Serial.println(F("===> PUSH REQUESTS"));

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
			/*HttpRequest* req1 = new TestGetRequest();
			HttpRequest* req2 =
					new PostSurgeRequest(123456, 1, 100000, 1000);
			HttpRequest* req3 = new PostBatteryRequest(415, 200, 0);
			requestManager->pushRequest(req1);
			requestManager->pushRequest(req2);
			requestManager->pushRequest(req3);*/
		}

		//Serial.print(F("Free RAM AFTER= "));
		//Serial.println(freeMemory(), DEC);

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
