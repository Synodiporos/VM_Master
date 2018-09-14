/*
 * RequestManager.h
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_REQUESTMANAGER_H_
#define WIFI_REQUESTMANAGER_H_

//#include <queue>
#include <Arduino.h>
//#include <WiFiEsp.h>
#include "SoftwareSerial.h"
#include "../Memory/MemoryFree.h"
#include "../System/SystemConstants.h"
#include "../Commons/Action.h"
#include "../Commons/IActionListener.h"
#include "HttpRequest.h"
#include "PostSurgeRequest.h"

#define CAPACITY 8
#define POSTING 1

#define ST_OFF 0
#define ST_BLUGED 1
#define ST_INITIALIZING 3
#define ST_INITIALIZED 4

#define ST_W_DISCONNECTED 10
#define ST_W_CHECK 11
#define ST_W_CONNECTING 12
#define ST_W_CONNECTED 13

#define ST_S_DISCONNECTED 20
#define ST_S_CHECK 21
#define ST_S_CONNECTING 22
#define ST_S_CONNECTED 23

#define ST_P_STOP_POSTING 100
#define ST_P_POSTING 101
#define ST_P_POST_REQUEST 102
#define ST_P_SEND_REQUEST 103

#define ST_RESP_OK "OK"

class RequestManager {
public:

	static RequestManager* getInstance();
	virtual ~RequestManager();

	void initialize();
	uint8_t size();
	void setActionListener(IActionListener* listener);
	IActionListener* getActionListener();

	bool pushRequest(HttpRequest* request);
	HttpRequest* topRequest();
	HttpRequest* popRequest();

	void checkESPModule();
	void checkWiFiConnection();
	void checkServerConnection();

	void initializeModule();
	void connectToWiFi();
	void connectToServer();

	bool startPosting();
	bool stopPosting();
	bool setEnabled(bool enabled);
	bool isEnabled();
	bool isPosting();

	void validate();

private:
	static RequestManager* instance;
	SoftwareSerial* esp = new SoftwareSerial(RX3_PIN, TX3_PIN); // RX, TX
	uint8_t _size = 0;
	HttpRequest* buf[CAPACITY];
	uint8_t index = 0;
	uint8_t posting = false;
	uint8_t enabled = false;

	uint8_t state = 0;
	uint8_t help = 0; //200 WAIT
	unsigned long time = millis();
	unsigned long timeout = millis();
	unsigned int waitTime = 0;
	uint8_t cc = 0;
	std::string currentRequest;
	IActionListener* actionListener = nullptr;

	RequestManager();
	void fill();
	void wait(unsigned int interval);
	void postRequest();
	bool setState(uint8_t oldState);
	void onStateChanged(uint8_t state);
	void onEspMessageReceived(const std::string msg);

	void onPostRequest(HttpRequest* request);
	void onGetRequest(HttpRequest* request);
	void sendRequest();
	void onResponseReceived(std::string response);
	void onACKReceived(std::string ack);
	void notifyActionPerformed(Action action);

};

#endif /* WIFI_REQUESTMANAGER_H_ */
