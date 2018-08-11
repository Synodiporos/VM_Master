/*
 * RFTransceiver.h
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#ifndef RFTRANSCEIVER_RFTRANSCEIVER_H_
#define RFTRANSCEIVER_RFTRANSCEIVER_H_
#include "../System/SystemConstants.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include "../Timer/Timer.h"
#include <SPI.h>
#include <RF24.h>

class RFTransceiver{
public:
	static const unsigned short int ON_CONNECTION_STATE = 90;
	static const unsigned short int ON_MESSAGE_RECEIVED = 91;
	static const unsigned short int ON_MESSAGE_SEND = 92;
	virtual ~RFTransceiver();
	static RFTransceiver* getInstance();
	void initialize(RF24* radio);
	bool isRadioStarted();
	bool isConnected();
	void startConnectivityCheck();
	void stopConnectivityCheck();
	void setActionListener(IActionListener* listener);
	//void setCheckForConnectivity(bool enabled);
	//bool isCheckForConnectinty();
	bool write(const char* msg);
	void printDetails();
	void validate();

private:
	RF24* radio = nullptr;
	static RFTransceiver* instance;
	bool connected = false;
	unsigned long time = 0;
	uint8_t ccCount = 4; //4=Stop
	bool radioStarted = false;
	//uint8_t ccSend = 0;
	IActionListener* actionListener = nullptr;
	RFTransceiver();

	void validateConnectivity();
	void setConnectionState(bool state);
	void resetCCTimer();
	void onMessageSend(const char* msg);
	void onMessageReceived(const char* msg);
	void onConnectionStateChanged(bool state);
	void notifyActionPerformed(Action& action);
	void onSendACK(uint8_t count);
};

#endif /* RFTRANSCEIVER_RFTRANSCEIVER_H_ */
