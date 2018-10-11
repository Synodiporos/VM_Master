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
#include "HttpRequestCreator.h"
#include "HttpResponse.h"

#define CAPACITY 8
#define SERIAL_BUFFER 48

#define ST_OFF 0
#define ST_BLUGED 1
#define ST_INITIALIZING 2
#define ST_INITIALIZE_ERROR 3
#define ST_INITIALIZED 4

#define ST_W_DISCONNECTED 10
#define ST_W_CHECK 11
#define ST_W_CONNECTING 12
#define ST_W_CONNECTING_FAIL 13
#define ST_W_CONNECTED 14

#define ST_S_DISCONNECTED 20
#define ST_S_CONNECTING 22
#define ST_S_ERROR 23
#define ST_S_CONNECTED 24

#define ST_P_POSTING_OFF 50
#define ST_P_POSTING_ON 51
#define ST_P_POSTING_READY 52 // WHEN CONNECTED TO SERVER
#define ST_P_POSTING_REQUEST 53
#define ST_P_SEND_REQUEST 54
#define ST_P_WAIT_RESP 60
#define ST_P_WAIT_RESP_PARSE_CODE 62
#define ST_P_WAIT_RESP_PARSE_CLENGHT 63
#define ST_P_WAIT_RESP_PARSE_CTYPE 64
#define ST_P_WAIT_RESP_PARSE_CONTENT 65
#define ST_P_WAIT_RESP_PARSING_COMPLETED 66
#define ST_P_REQUEST_POSTED 80
#define ST_P_REQUEST_POST_ERROR 81

#define RESP_OK "OK"
#define RESP_WIFI_DISC "WIFI DISC"
#define RESP_WIFI_CONN "GOT IP"
#define RESP_WIFI_FAIL "FAIL"
#define RESP_SERVER_CONNECT "CONNECT"
#define RESP_SERVER_CLOSED "CLOSED"
#define RESP_SERVER_FAIL "CONNECT FAIL"
#define RESP_SERVER_SEND "SEND OK"
#define RESP_SERVER_ER "1.1 40"
#define RESP_SERVER_OK "1.1 200"

#define HTTP_RESP_CODE "HTTP/1.1"
#define HTTP_RESP_CLENGHT "Content-Length:"
#define HTTP_RESP_CTYPE "Content-Type:"

class RequestManager {
public:

	static RequestManager* getInstance();
	virtual ~RequestManager();

	void initialize();
	uint8_t size();
	uint8_t getState();
	uint8_t getPostingState();

	void setActionListener(IActionListener* listener);
	IActionListener* getActionListener();

	bool pushRequest(HttpRequest* request);
	HttpRequest* topRequest();
	HttpRequest* popRequest();

	void checkESPModule();
	void checkWiFiConnection();

	void initializeModule();
	void setAutoConnect(bool autoC);
	void connectToWiFi();
	void connectToServer();
	void disconnectToServer();

	bool setEnabled(bool enabled);
	bool isEnabled();
	bool startPosting();
	bool stopPosting();
	bool isPosting();
	bool isInitialized();
	bool isWifiConnected();
	bool isServerConnected();
	bool isReadyToPost();

	void validate();

private:
	static RequestManager* instance;
	SoftwareSerial* esp = new SoftwareSerial(RX3_PIN, TX3_PIN); // RX, TX
	uint8_t _size = 0;
	HttpRequest* buf[CAPACITY];
	uint8_t index = 0;
	uint8_t enabled = false;
	uint8_t state = 0;
	uint8_t postState = 0;
	uint8_t help = 0; //200 WAIT
	//unsigned long time = millis();
	unsigned long timeout = millis();
	unsigned long timeoutP = millis();
	unsigned int waitTime = 0;
	char request[WIFI_REQUEST_LENGHT];
	HttpRequest* httpReq;
	HttpResponse response;
	IActionListener* actionListener = nullptr;

	RequestManager();
	void fill();
	void wait(unsigned int interval);
	void postNextRequest();
	void postRequest(HttpRequest* request);
	bool setState(uint8_t state);
	bool setPostingState(uint8_t state);
	void onEspMessageReceived(const String& msg);
	void readStream();
	void validatePosting();


	void onStateChanged();
	void onPostingStateChanged();
	void onPostRequest(HttpRequest* request);
	void onGetRequest(HttpRequest* request);
	void sendRequest();
	void onResponseParcing(const String& response);
	void onResponseReceived(const HttpResponse& response);
	void onACKReceived(const char* ack);
	void notifyActionPerformed(Action action);

};

#endif /* WIFI_REQUESTMANAGER_H_ */
