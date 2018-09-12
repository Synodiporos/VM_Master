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
//#include "WiFiEsp.h"
#include "SoftwareSerial.h"
#include "../Memory/MemoryFree.h"
#include "../System/SystemConstants.h"
#include "HttpRequest.h"
#include "PostSurgeRequest.h"

#define CAPACITY 8
#define POSTING 1

#define ST_OFF 0
#define ST_BLUGED 100
#define ST_INITIALIZING 1
#define ST_INITIALIZED 2
#define ST_CONNECTING 3
#define ST_CONNECTED 4
#define ST_DISCONNECTED 5

class RequestManager {
public:
	RequestManager();
	virtual ~RequestManager();

	void initialize();
	uint8_t size();
	bool pushRequest(HttpRequest* request);
	HttpRequest* topRequest();
	HttpRequest* popRequest();

	void checkESPModule();
	void initializeModule();
	void connectToWiFi();
	void checkWiFiConnection();


	bool startPosting();
	bool stopPosting();
	bool isPosting();

	void validate();

private:
	//std::queue<HttpRequest*> buffer;
	SoftwareSerial* esp = new SoftwareSerial(RX3_PIN, TX3_PIN); // RX, TX
	//SoftwareSerial* esp; // RX, TX
	//WiFiEspClient client;

	uint8_t _size = 0;
	HttpRequest* buf[CAPACITY];
	uint8_t index = 0;
	bool posting = false;
	//0:OFF, 1:INITializing, 2:INIT, 3:CONNECTING, 4:CONNECTED
	uint8_t state = 0;
	//uint8_t count = 0;

	unsigned long time = millis();
	unsigned long timeout = millis();
	uint8_t cc = 0;

	void fill();
	bool setState(uint8_t oldState);
	void onStateChanged(uint8_t state);
	bool onPostRequest(HttpRequest* request);
	void onEspMessageReceived(const std::string msg);
	void onResponseReceived(std::string response);
	void onACKReceived(std::string ack);

};

#endif /* WIFI_REQUESTMANAGER_H_ */
