/*
 * RequestManager.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "RequestManager.h"

const char RequestManager::OK[3] = "OK";

RequestManager* RequestManager::instance = nullptr;

RequestManager::RequestManager(){
	// TODO Auto-generated constructor stub

	initialize();
}

RequestManager::~RequestManager() {
	// TODO Auto-generated destructor stub
}

RequestManager* RequestManager::getInstance(){
	if(!instance)
		instance = new RequestManager();
	return instance;
}

void RequestManager::initialize(){
	for(int i=0; i<CAPACITY; i++){
		buf[i] = nullptr;
	}

	esp->begin(SRL3_BD);
	//esp->setTimeout(500);
	//esp->println(F("AT"));
}

void RequestManager::setActionListener(IActionListener* listener){
	if(this->actionListener!=listener){
		this->actionListener = listener;
		//return true;
	}
	//return false;
}

IActionListener* RequestManager::getActionListener(){
	return this->actionListener;
}


uint8_t RequestManager::size(){
	return this->_size;
}

uint8_t RequestManager::getState(){
	return this->state;
}

uint8_t RequestManager::getPostingState(){
	return this->postState;
}

uint8_t RequestManager::getWiFiState(){
	return this->wifiState;
}

uint8_t RequestManager::getServerState(){
	return this->serverState;
}

bool RequestManager::pushRequest(HttpRequest* request){
	//buffer.push(request);
	Serial.print(F("+ PUSH index:"));
	Serial.print(index);
	Serial.print(F(" pointer:"));
	Serial.print((long)request);

	if(_size<CAPACITY){
		uint8_t i = index + _size;
		if(i>=CAPACITY)
			i = i%CAPACITY;

		Serial.print(F(" i="));
		Serial.println(i);

		buf[i] = request;
		_size++;
	}
	else{
		HttpRequest* req = buf[index];
		buf[index] = nullptr;
		delete req;
		buf[index] = request;
		index++;
		if(index>=CAPACITY)
			index = 0;
	}


	Serial.print(F(" size:"));
	Serial.print(_size);

	Serial.print(F(" Free RAM = "));
	Serial.println(freeMemory(), DEC);

	return true;
}

HttpRequest* RequestManager::topRequest(){
	if(_size>0){
		return buf[index];
	}
	return nullptr;
}

HttpRequest* RequestManager::popRequest(){
//	if(buffer.size()>0){
//		HttpRequest* r = buffer.front();
//		buffer.pop();
//		return r;
//	}
	Serial.print(F("-  Pop index:"));
	Serial.print(index);

	if(this->_size>0){
		HttpRequest* req =  buf[index];
		//if(req)
		//	delete req;
		buf[index] = nullptr;

		index++;
		if(index>=CAPACITY)
			index = 0;
		_size--;

		Serial.print(F(" size:"));
		Serial.print(_size);
		Serial.print(F(" pointer:"));
		Serial.print((long)req);

		Serial.print(F(" Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
		Serial.print(freeMemory(), DEC);
		Serial.println();
		return req;
	}
	return nullptr;
}

void RequestManager::checkESPModule(){
	esp->println(F("AT"));
}

void RequestManager::initializeModule(){
	//esp->println(F("AT+CWMODE=3"));
	esp->println(F("AT"));
	timeout = millis();
	setState(ST_INITIALIZING);
}

void RequestManager::setAutoConnect(bool autoC){
	if(autoC)
		esp->println(F("AT+CWAUTOCONN=1"));
	else
		esp->println(F("AT+CWAUTOCONN=0"));
	setState(ST_INITIALIZING_2);
	timeout = millis();
}

void RequestManager::connectToWiFi(){
	char at[64];
	sprintf (at, "AT+CWJAP_CUR=\"%s\",\"%s\"",
			WIFI_SSID, WIFI_PASS);

	//Serial.println(at);
	esp->println(at);
	setState(ST_W_CONNECTING);

	timeout = millis();
}

void RequestManager::connectToServer(){
	char at[64];
	sprintf (at, "AT+CIPSTART=\"TCP\",\"%s\",80",
			WIFI_SERVER);

	//Serial.println(at);
	esp->println(at);
	setState(ST_S_CONNECTING);

	timeout = millis();
}

void RequestManager::disconnectToServer(){
	esp->println(F("AT+CIPCLOSE"));
}

void RequestManager::checkWiFiConnection(){
	setState(ST_W_CHECK);
	//Serial.println(F("AT+CWJAP?"));
	esp->println("AT+CWJAP?");
	timeout = millis();
}

void RequestManager::checkServerConnection(){
	//2: The ESP8266 Station is connected to an AP and its IP is obtained.
	//3: The ESP8266 Station has created a TCP or UDP transmission.
	//4: The TCP or UDP transmission of ESP8266 Station is disconnected.
	//5: The ESP8266 Station does NOT connect to an AP

	esp->println("AT+CIPSTATUS");
	setState(ST_S_CHECK);
	timeout = millis();
}

bool RequestManager::setEnabled(bool enabled){
	if(this->enabled!=enabled){
		this->enabled = enabled;
		return true;
	}
	return false;
}

bool RequestManager::isEnabled(){
	return enabled;
}

bool RequestManager::startPosting(){
	if(getPostingState()<ST_P_POSTING_ON){
		setPostingState(ST_P_POSTING_ON);
		return true;
	}
	return false;
}

bool RequestManager::stopPosting(){
	if(getPostingState()!=ST_P_POSTING_OFF){
		setPostingState(ST_P_POSTING_OFF);
		return true;
	}
	return false;
}

bool RequestManager::isPosting(){
	return this->getPostingState()>=ST_P_POSTING_ON;
}

bool RequestManager::isInitialized(){
	return this->state==ST_INITIALIZED_2;
}

bool RequestManager::isWifiConnected(){
	return this->wifiState==ST_W_CONNECTED;
}

bool RequestManager::isServerConnected(){
	return this->serverState==ST_S_CONNECTED;
}

void RequestManager::validate(){
	readStream();
	if(!isEnabled())
		return;

	if(waitTime>0){
		if(millis()-timeout>waitTime){
			timeout = millis();
			waitTime = 0;
		}else{
			return;
		}
	}

	switch(getState()){
		case ST_OFF:{
			initializeModule();
			break;
		}
		case ST_INITIALIZING:{
			if(millis()-timeout>4000){
				//initializeModule();
				esp->println(F("AT+RST"));
				timeout = millis();
			}
			break;
		}
		case ST_INITIALIZING_2:{
			if(millis()-timeout>3000){
				initializeModule();
				timeout = millis();
			}
			break;
		}
		case ST_INITIALIZED:{

			break;
		}
		case ST_INITIALIZED_2:{

			break;
		}
		case ST_W_CHECK:{
			if(millis()-timeout>5000){
				//setState(ST_W_DISCONNECTED);
				timeout = millis();
			}
			break;
		}
		case ST_W_CONNECTING:{
			if(millis()-timeout>=16000){
				setState(ST_W_CONNECTING_FAIL);
				timeout = millis();
			}
			break;
		}
		case ST_W_CONNECTING_FAIL:{
			if(millis()-timeout>=12000){
				//setState(ST_W_CONNECTING);
				//connectToWiFi();
			}
			break;
		}
		case ST_W_CONNECTED:{
			//CHECK WIFI CONNECTION
			if(millis()-timeout>=WIFI_CHECK_INTERVAL){
				checkWiFiConnection();
				timeout = millis();
			}
			if(isPosting() && size()>0){
				connectToServer();
			}
			break;
		}
		case ST_W_DISCONNECTED:{
			//CHECK WIFI CONNECTION
			if(millis()-timeout>=WIFI_CHECK_INTERVAL){
				checkWiFiConnection();
				timeout = millis();
			}
			break;
		}
		case ST_S_CHECK:{
			//connectToServer();
			if(millis()-timeout>=4000){
				setState(ST_S_DISCONNECTED);
				timeout = millis();
			}
			break;
		}
		case ST_S_CONNECTING:{
			if(millis()-timeout>=5000){
				setState(ST_S_DISCONNECTED);
				timeout = millis();
			}
			break;
		}
		case ST_S_CONNECTED:{
			if(millis()-timeoutP>=10000){
				disconnectToServer();
				timeoutP = millis();
			}
			break;
		}
		case ST_S_DISCONNECTED:{
			//CHECK WIFI CONNECTION
			if(millis()-timeout>=WIFI_CHECK_INTERVAL){
				checkWiFiConnection();
				timeout = millis();
			}
			break;
		}
	}

	validatePosting();
}

void RequestManager::readStream(){
	char buffer[SERIAL_BUFFER];
	uint8_t count = 0;
	if (esp->available()){
		while (esp->available() > 0 ){
			count =  esp->readBytesUntil('\n', buffer, SERIAL_BUFFER);
			if(count>0){
				String response(buffer);
				response.trim();
				if(response.length()>0)
					onEspMessageReceived(response);
				memset(buffer, 0, sizeof(buffer));   // Clear contents of Buffer
			}
		}
	}
}

void RequestManager::validatePosting(){
	switch(getPostingState()){
		case ST_P_POSTING_ON:{
			if(size()>0){
				if(state==ST_S_CONNECTED){
					postNextRequest();
				}
				else if(state>=ST_W_CONNECTED){
					connectToServer();
				}
			}
			break;
		}
		case ST_P_POSTING_READY:{

			break;
		}
		case ST_P_POSTING_REQUEST:{
			if(millis()-timeoutP>15000){
				setPostingState(ST_P_POSTING_ON);
				timeoutP = millis();
			}
			break;
		}
		case ST_P_SEND_REQUEST:{
			if(millis()-timeoutP>15000){
				setPostingState(ST_P_POSTING_ON);
				timeoutP = millis();
			}
			break;
		}
		case ST_P_WAIT_RESP:{
			if(millis()-timeoutP>10000){
				setPostingState(ST_P_REQUEST_POST_ERROR);
				wait(1000);
			}
			break;
		}
		case ST_P_REQUEST_POSTED:{

			break;
		}
		case ST_P_REQUEST_POST_ERROR:{

			break;
		}
	}
}

void RequestManager::fill(){

	for(int i=0; i<35; i++){
		PostSurgeRequest* req = new PostSurgeRequest(i, 0, 0);
		pushRequest(req);
	}
	//delay(20);
}

void RequestManager::wait(unsigned int interval){
	waitTime = interval;
	timeout = millis();
}

bool RequestManager::setState(uint8_t state){
	if(this->state!=state){
		uint8_t old = this->state;
		this->state = state;
		onStateChanged(old);
		return true;
	}
	return false;
}

bool RequestManager::setPostingState(uint8_t state){
	if(this->postState!=state){
		uint8_t old = this->postState;
		this->postState = state;
		onPostingStateChanged(old);
		return true;
	}
	return false;
}

void RequestManager::onStateChanged(uint8_t oldState){
	Action action(this, getState(), nullptr, nullptr);
	notifyActionPerformed(action);

	switch(getState()){
		case ST_INITIALIZED:{
			setAutoConnect(WIFI_AUTOCONNECT);
			break;
		}
		case ST_INITIALIZED_2:{
			connectToWiFi();
			break;
		}
		case ST_W_CONNECTED:{
			//wait(6000);
			//connectToServer();
			break;
		}
		case ST_W_DISCONNECTED:{
			//if(isToBeConnected)
			//	connectToWiFi();
			break;
		}
		case ST_S_CONNECTED:{
		//	postRequest();
			break;
		}
	}

	Serial.print(F("$ Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);
	wait(50);
}

void RequestManager::onPostingStateChanged(uint8_t oldState){
	Action action(this, postState, nullptr, nullptr);
	notifyActionPerformed(action);

	switch(getPostingState()){
		case ST_P_POSTING_READY:{
			timeoutP = millis();
			break;
		}
		case ST_P_POSTING_REQUEST:{

			break;
		}
		case ST_P_SEND_REQUEST:{
			timeoutP = millis();
			break;
		}
		case ST_P_WAIT_RESP:{
			timeoutP = millis();
			break;
		}
		case ST_P_REQUEST_POSTED:{
			timeoutP = millis();
			popRequest();
			setPostingState(ST_P_POSTING_ON);
			wait(1000);
			break;
		}
		case ST_P_REQUEST_POST_ERROR:{
			timeoutP = millis();
			setPostingState(ST_P_POSTING_ON);
			wait(5000);
			break;
		}
	}
}

void RequestManager::onServerStateChanged(uint8_t oldState){
	Action action(this, getState(), nullptr, nullptr);
	notifyActionPerformed(action);

	switch(getServerState()){
		case ST_S_DISCONNECTED:{

			break;
		}
	}
}

void RequestManager::onEspMessageReceived(const String& msg){
	Serial.print(F("-- Received: "));
	const char* c = msg.c_str();
	Serial.println(c);

	switch(state){
		case ST_OFF:{
			if(msg.compareTo(OK)==0){
				setState(ST_BLUGED);
			}
			break;
		}
		case ST_INITIALIZING:{
			if(msg.compareTo(OK)==0){
				setState(ST_INITIALIZED);
			}
			break;
		}
		case ST_INITIALIZING_2:{
			if(msg.indexOf("AT+CWA")){
				help = 'A';
			}
			if(msg.compareTo(OK)==0 && help=='A'){
				setState(ST_INITIALIZED_2);
				help = 0;
			}
			break;
		}
		case ST_INITIALIZED:{

			break;
		}
		case ST_INITIALIZED_2:{

			break;
		}
		case ST_W_CHECK:{
			if(msg.compareTo(OK)==0){
				if(help=='O')
					setState(ST_W_CONNECTED);
				else
					setState(ST_W_DISCONNECTED);
				help = 0;
			}
			if(msg.indexOf("+CWJAP:") >= 0){
				if(msg.indexOf(WIFI_SSID) > 0){
					help = 'O';
				}
				else{
					help = 'F';
				}
			}
			else if(msg.indexOf("No AP:") >= 0){
				setState(ST_W_DISCONNECTED);
				connectToWiFi();
			}
			break;
		}
		case ST_W_CONNECTING:{
			if(msg.compareTo(OK)==0 && help=='I'){
				setState(ST_W_CONNECTED);
				help = 0;
			}
			else if(msg.indexOf("FAIL") >= 0){
				//setState(ST_W_DISCONNECTED);
				setState(ST_W_CONNECTING_FAIL);
			}
			if(msg.compareTo(RESP_WIFI_CONN)==0){
				help = 'I';
			}
			break;
		}
		case ST_W_CONNECTED:{
			if(msg.compareTo(RESP_WIFI_DISC)==0){
				setState(ST_W_DISCONNECTED);
			}
			break;
		}
		case ST_W_DISCONNECTED:{
			if(msg.compareTo(RESP_WIFI_CONN)==0){
				setState(ST_W_CONNECTED);
			}
			break;
		}
		case ST_S_CHECK:{
			if(msg.compareTo(OK)==0){
				if(help == '2' || help == '3'){
					setState(ST_S_CONNECTED);
				}
				else{
					setState(ST_S_DISCONNECTED);
					connectToServer();
				}
				help = 0;
			}
			if(msg.compareTo("STATUS:2") == 0){
				help = '2';
			}
			else if(msg.compareTo("STATUS:3") == 0){
				help = '3';
			}
			break;
		}
		case ST_S_CONNECTING:{
			if(help==25 && msg.compareTo(OK) == 0){
				setState(ST_S_CONNECTED);
			}
			else if(msg.compareTo(RESP_SERVER_CLOSED) == 0){
				setState(ST_S_DISCONNECTED);
			}
			else if(msg.startsWith("ALR")){
				help = 24;
			}
			else if(msg.indexOf(RESP_SERVER_CONNECT)>=0){
				help = 25;
			}
			if(help==24 && msg.startsWith("E")){
				setState(ST_S_CONNECTED);
			}
			break;
		}
		case ST_S_CONNECTED:{
			if(msg.compareTo(RESP_SERVER_CLOSED) == 0){
				setState(ST_S_DISCONNECTED);
			}
			break;
		}
		case ST_S_DISCONNECTED:{

			break;
		}
	}

	if(getState()>=ST_W_CONNECTED)
		if(msg.compareTo(RESP_WIFI_CONN)==0){
			setState(ST_W_CONNECTED);
			wait(250);
		}

	if(isPosting())
	switch(getPostingState()){
		case ST_P_POSTING_ON:{
			break;
		}
		case ST_P_POSTING_REQUEST:{
			if(msg.indexOf(">") >= 0) {
				sendRequest();
			}
			break;
		}
		case ST_P_SEND_REQUEST:{
			if(msg.compareTo("SEND OK") == 0) {
				setPostingState(ST_P_WAIT_RESP);
			}
			break;
		}
		case ST_P_WAIT_RESP:{
			onResponseReceived(msg);
			if(millis()-timeoutP>10000){
				Serial.println(F("... WAIT RESP TIMEOUT!"));
				setPostingState(ST_P_POSTING_READY);
				timeoutP = millis();
			}
			break;
		}
	}
	//delay(50);
	//delete c;
}

void RequestManager::postNextRequest(){
	HttpRequest* next = topRequest();
	if(next){
		postRequest(next);
	}
	timeoutP = millis();
}

void RequestManager::postRequest(HttpRequest* httpRequest) {
	Serial.print(F("$ Free RAM = "));
	Serial.println(freeMemory(), DEC);

	if(httpRequest){
		char* req = httpRequest->getRequest();

		//onPostRequest(httpRequest);

		String request(req);
		Serial.println(request);

		Serial.print(F("Post Request text: "));
		Serial.println( request.length() );

		//String sendCmd = "AT+CIPSEND="; //determine the number of caracters to be sent.
		esp->print(F("AT+CIPSEND="));
		esp->println(request.length()-0);

		setPostingState(ST_P_POSTING_REQUEST);
		timeoutP = millis();
		this->request = request;
	}
}

void RequestManager::onPostRequest(HttpRequest* request){
	Serial.print(F("On Post: "));
	Serial.println(request->getRequest());
}

void RequestManager::onGetRequest(HttpRequest* request){

}

void RequestManager::sendRequest(){
	setPostingState(ST_P_SEND_REQUEST);
	timeoutP = millis();
	//Serial.println(F("Sending..."));
	//Serial.println(request);
	esp->print(request);
}

void RequestManager::onResponseReceived(const String& response){
	if(response.indexOf(RESP_SERVER_OK)>=0){
		setPostingState(ST_P_REQUEST_POSTED);
	}
	else if(response.indexOf(RESP_SERVER_ER)>=0){
		setPostingState(ST_P_REQUEST_POST_ERROR);
	}
	else{
		//setPostingState(ST_P_REQUEST_POST_ERROR);
	}
}

void RequestManager::onACKReceived(const char* ack){

}

void RequestManager::notifyActionPerformed(Action action){
	IActionListener* listener = getActionListener();
	if(listener!=nullptr){
		listener->actionPerformed(action);
	}
}

