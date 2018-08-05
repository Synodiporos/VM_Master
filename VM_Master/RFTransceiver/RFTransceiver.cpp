/*
 * RFTransceiver.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#include "RFTransceiver.h"

RFTransceiver* RFTransceiver::instance = nullptr;

RFTransceiver::~RFTransceiver() {
	// TODO Auto-generated destructor stub
}

RFTransceiver::RFTransceiver() {
	// TODO Auto-generated constructor stub
	//initialize();
}

RFTransceiver* RFTransceiver::getInstance(){
	if(instance==nullptr){
		instance = new RFTransceiver();
	}
	return instance;
}

void RFTransceiver::initialize(RF24* radio){
	this->radio = radio;
	Serial.println((long)radio);
	if(radio->begin()){
		radio->openWritingPipe(RF_WRITE_PIPE); // 00001
		radio->openReadingPipe(1, RF_READ_PIPE); // 00002
		radio->setPALevel(RF24_PA_MIN);

		Serial.println(F("Radio Begin"));
	}
	else{
		Serial.println(F("Radio ERROR"));
	}
}

void RFTransceiver::setActionListener(IActionListener* listener){
	this->actionListener = listener;
}

uint8_t RFTransceiver::write(const char* msg){
	Serial.print(F("RF Sent: "));
	Serial.println(msg);

	radio->stopListening();
	radio->write(msg, sizeof(msg));
	//delay(1);
	radio->startListening();
	return 1;
}

void RFTransceiver::validate(){
	unsigned long interval = millis()-time;
	uint8_t ccIntervals = 5;
	unsigned int period = RF_CC_PERIOD;
	if(interval > period){
		/*if(interval > period + 1*ccIntervals
				&& ccSend==1){
			setConnectionState(false);
			resetCCTimer();
			ccSend = 0;
		}
		if(ccSend==0){
			const char* msg = "Test MSG!";
			write(msg);
			ccSend = 1;
		}*/
	}
	if(radio->available()){
		char msg[32] = "";
		radio->read(msg, sizeof(msg));
		onMessageReceived(msg);
	}
}

void RFTransceiver::resetCCTimer(){
	this->time = millis();
}

void RFTransceiver::setConnectionState(bool state){
	if(isConnected != state){
		isConnected = state;
		onConnectionStateChanged(state);
		Action action(this, ON_CONNECTION_STATE, nullptr, nullptr);
		notifyActionPerformed(action);
	}
}

void RFTransceiver::onMessageReceived(char* msg){
	Serial.print(F("Message Received: "));
	Serial.print(msg);

	resetCCTimer();
	ccCount = 0;
	setConnectionState(true);

	Action action(this, ON_MESSAGE_RECEIVED, nullptr, msg);
	notifyActionPerformed(action);
}

void RFTransceiver::onConnectionStateChanged(bool state){
	Serial.println(F("Connection State: "));
	Serial.print(state);
}

void RFTransceiver::notifyActionPerformed(Action& action){
	if(this->actionListener)
		this->actionListener->actionPerformed(action);
}
