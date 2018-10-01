/*
 * RFTransceiver.h
 *
 *  Created on: Jul 6, 2018
 *      Author: sgeorgiadis
 */

#ifndef RFTRANSCEIVER_RFTRANSCEIVER_H_
#define RFTRANSCEIVER_RFTRANSCEIVER_H_
#include <SPI.h>
#include <RF24.h>
#include "../System/SystemConstants.h"
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include "../Timer/Timer.h"
#include "../Util/CharUtil.h"

#define RF_STATE_OFF 0
#define RF_STATE_INITIALIZE_ERROR 1
#define RF_STATE_INITIALIZED 2

#define RF_STATE_REQUEST_ERROR 10
#define RF_STATE_REQUEST_SENDING 11
#define RF_STATE_REQUEST_SEND 30

#define RF_RETRIES 3
#define RF_CONNECTION_CHECK_INTERVALS 128


class RFTransceiver{
public:
	static const unsigned short int ON_CONNECTION_STATE = 90;
	static const unsigned short int ON_MESSAGE_RECEIVED = 91;
	static const unsigned short int ON_RESPONSE_RECEIVED = 92;
	static const unsigned short int ON_MESSAGE_SEND = 93;
	static const unsigned short int ON_MESSAGE_SEND_ERROR = 94;
	static const unsigned short int ON_REQUEST_SEND_OK = 95;
	static const unsigned short int ON_REQUEST_SEND_FAIL = 96;
	static const unsigned short int ON_ACTIVE_STATE = 97;

	virtual ~RFTransceiver();
	static RFTransceiver* getInstance();
	bool setEnabled(bool enabled);
	bool isEnabled();
	uint8_t getState();
	void initialize();
	bool isActivated();
	bool isInitialized();
	bool isSending();
	bool isConnected();
	//void startConnectivityCheck();
	//void stopConnectivityCheck();
	void setActionListener(IActionListener* listener);
	bool powerUp();
	bool powerDown();
	bool startListening();
	bool stopListening();
	bool isListening();
	bool write(const char* msg);
	bool send(const char* msg, uint8_t ackId);
	void printDetails();
	void validate();

private:
	RF24 radio = RF24(RF_CE, RF_CSN);
	static RFTransceiver* instance;
	bool enabled = false;
	bool active = true;
	uint8_t state = RF_STATE_OFF;
	bool listen = false;
	uint8_t helper = 0;
	unsigned long time = 0;
	char request[24];
	uint8_t requestId = 0;
	IActionListener* actionListener = nullptr;
	RFTransceiver();

	bool setActiveState(bool active);
	void onActiveStateChanged();
	bool setState(uint8_t state);
	void onStateChanged();
	void onMessageSend(const char* msg);
	void onMessageSendError(const char* msg);
	void onRequestPosted(const char* msg, uint8_t id);
	void onRequestPostError(const char* msg, uint8_t id);
	void onMessageReceived(const char* msg);
	void onResponseReceived(const char* msg, uint8_t id);
	void onSendRequest();
	void notifyActionPerformed(Action& action);
};

#endif /* RFTRANSCEIVER_RFTRANSCEIVER_H_ */
