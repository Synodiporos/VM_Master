/*
 * RequestManager.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "RequestManager.h"

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
	for(int i=0; i<BUFFER_CAPACITY; i++){
		buf[i] = nullptr;
	}
	setState(ST_OFF);
	esp->begin(SRL3_BD);
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

bool RequestManager::pushRequest(HttpRequest* request){
	//buffer.push(request);
	/*Serial.print(F("+ PUSH index:"));
	Serial.print(index);
	Serial.print(F(" pointer:"));
	Serial.println((long)request);


	char buffer[WIFI_REQUEST_LENGHT];
	uint8_t size =
			HttpRequestCreator::createRequest(buffer, request);
	Serial.println(F("STRING:"));
	Serial.println(buffer);*/

	if(_size<BUFFER_CAPACITY){
		uint8_t i = index + _size;
		if(i>=BUFFER_CAPACITY)
			i = i%BUFFER_CAPACITY;

		/*Serial.print(F(" i="));
		Serial.println(i);*/

		buf[i] = request;
		_size++;
	}
	else{
		HttpRequest* req = buf[index];
		buf[index] = nullptr;
		delete req;
		buf[index] = request;
		index++;
		if(index>=BUFFER_CAPACITY)
			index = 0;
	}


	/*Serial.print(F(" size:"));
	Serial.print(_size);

	Serial.print(F(" Free RAM = "));
	Serial.println(freeMemory(), DEC);*/

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
	/*Serial.print(F("-  Pop index:"));
	Serial.print(index);*/

	if(this->_size>0){
		HttpRequest* req =  buf[index];
		//if(req)
		//	delete req;
		buf[index] = nullptr;

		index++;
		if(index>=BUFFER_CAPACITY)
			index = 0;
		_size--;

		/*Serial.print(F(" size:"));
		Serial.print(_size);
		Serial.print(F(" pointer:"));
		Serial.print((long)req);

		Serial.print(F(" Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
		Serial.print(freeMemory(), DEC);
		Serial.println();*/
		return req;
	}
	return nullptr;
}

void RequestManager::checkESPModule(){
	esp->println(F("AT"));
}

void RequestManager::initializeModule(){
	//esp->println(F("AT+CWMODE=3"));
	//esp->println(F("AT+CWMODE=3"));
	//delay(100);
	//setAutoConnect(true);
	esp->println(F("AT+RST"));
	wait(2000);
	timeout = millis();
	setState(ST_INITIALIZING);
}

void RequestManager::setAutoConnect(bool autoC){
	if(autoC)
		esp->println(F("AT+CWAUTOCONN=1"));
	else
		esp->println(F("AT+CWAUTOCONN=0"));
	//setState(ST_INITIALIZING_2);
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
	return this->state>=ST_INITIALIZED;
}

bool RequestManager::isWifiConnected(){
	return this->state>=ST_W_CONNECTED;
}

bool RequestManager::isServerConnected(){
	return this->state>=ST_S_CONNECTED;
}

bool RequestManager::isReadyToPost(){
	return isWifiConnected() &&
			postState == ST_P_POSTING_ON;
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
				//esp->println(F("AT+RST"));
				setState(ST_INITIALIZE_ERROR);
				timeout = millis();
			}
			break;
		}
		case ST_INITIALIZE_ERROR:{
			if(millis()-timeout>4000){
				initializeModule();
				timeout = millis();
			}
			break;
		}
		case ST_INITIALIZED:{
			if(millis()-timeout>8000){
				connectToWiFi();
				timeout = millis();
			}
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
		case ST_S_CONNECTING:{
			if(millis()-timeout>=10000){
				setState(ST_S_ERROR);
				timeout = millis();
			}
			break;
		}
		case ST_S_ERROR:{
			if(millis()-timeoutP>=30000){
				connectToServer();
				timeoutP = millis();
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



void RequestManager::validatePosting(){
	switch(getPostingState()){
		case ST_P_POSTING_ON:{
			if(size()>0){
				if(state==ST_S_CONNECTED){
					postNextRequest();
				}
				else if(state==ST_S_ERROR){

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


void RequestManager::onEspMessageReceived(const String& msg){
	Serial.print(F("-- Received: "));
	const char* c = msg.c_str();
	Serial.println(c);

	switch(state){
		case ST_OFF:{
			if(msg.compareTo(RESP_OK)==0){
				setState(ST_BLUGED);
			}
			return;
		}
		case ST_INITIALIZING:{
			if(msg.compareTo(RESP_OK)==0){
				setState(ST_INITIALIZED);
			}
			return;
		}
		case ST_INITIALIZED:{
			if(msg.indexOf(RESP_WIFI_CONN)>=0){
				setState(ST_W_CONNECTED);
			}
			return;
		}
		case ST_W_CHECK:{
			if(msg.compareTo(RESP_OK)==0){
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
			return;
		}
		case ST_W_CONNECTING:{
			if(msg.compareTo(RESP_OK)==0 && help=='I'){
				setState(ST_W_CONNECTED);
				help = 0;
			}
			else if(msg.indexOf(RESP_WIFI_FAIL) >= 0){
				//setState(ST_W_DISCONNECTED);
				setState(ST_W_CONNECTING_FAIL);
			}
			if(msg.indexOf(RESP_WIFI_CONN)>=0){
				help = 'I';
			}
			return;
		}
		case ST_W_CONNECTED:{

			break;
		}
		case ST_W_DISCONNECTED:{
			if(msg.indexOf(RESP_WIFI_CONN)>=0){
				setState(ST_W_CONNECTED);
			}
			return;
		}
		case ST_S_CONNECTING:{
			if(help==25 && msg.compareTo(RESP_OK) == 0){
				setState(ST_S_CONNECTED);
			}
			else if(msg.compareTo(RESP_SERVER_CLOSED) == 0){
				setState(ST_S_DISCONNECTED);
			}
			else if(msg.indexOf("ALR")>=0){
				help = 24;
			}
			else if(msg.compareTo(RESP_SERVER_CONNECT)==0){
				help = 25;
			}
			else if(msg.indexOf(RESP_SERVER_FAIL)>=0){
				help = 26;
			}
			if(msg.startsWith("ERR")){
				if(help==24)
					setState(ST_S_CONNECTED);
				else if(help==26)
					setState(ST_S_ERROR);
				else
					setState(ST_S_ERROR);
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

	if(msg.indexOf(RESP_WIFI_DISC)>=0){
		setState(ST_W_DISCONNECTED);
	}

	if(isPosting()){
		uint8_t pstate = getPostingState();
		if(pstate>=ST_P_WAIT_RESP && pstate<ST_P_REQUEST_POSTED){
			onResponseParcing(msg);
		}
		else{
			switch(pstate){
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
					if(msg.compareTo(RESP_SERVER_SEND) == 0) {
						setPostingState(ST_P_WAIT_RESP);
					}
					break;
				}
				//case ST_P_WAIT_RESP:{
					//onResponseReceived(msg);
				//	break;
				//}
			}
		}
	}

	if(msg.indexOf("busy")>=0){
		wait(2000);
		return;
	}
	//delay(50);
	//delete c;
}

void RequestManager::onResponseParcing(const String& response){

	uint8_t pstate = getPostingState();
	switch(pstate){
		case ST_P_WAIT_RESP:{
			int index = response.indexOf(HTTP_RESP_CODE);
			if(index>=0){
				uint8_t ii = index + strlen(HTTP_RESP_CODE)+1;
				String str = response.substring(ii, ii+3);
				uint8_t code = atoi(str.c_str());
				this->httpResponse.setHttpCode(code);
				setPostingState(ST_P_WAIT_CONTENT_START);
			}
			break;
		}
		case ST_P_WAIT_CONTENT_START:{
			int istart = response.indexOf("{");
			if(istart>=0){
				this->httpResponse.appendContent(response);
				setPostingState(ST_P_WAIT_CONTENT_END);
			}
			if(getPostingState()==ST_P_WAIT_CONTENT_END){
				int iend = response.indexOf("}");
				if(iend>=0){
					setPostingState(ST_P_RESPONSE_COMPLETED);
				}
			}
			break;
		}
		case ST_P_WAIT_CONTENT_END:{
			this->httpResponse.appendContent(response);
			int iend = response.indexOf("}");
			if(iend>=0){
				setPostingState(ST_P_RESPONSE_COMPLETED);
			}
			break;
		}
	}
}

void RequestManager::wait(unsigned int interval){
	waitTime = interval;
	timeout = millis();
}

bool RequestManager::setState(uint8_t state){
	if(this->state!=state){
		this->state = state;
		onStateChanged();
		return true;
	}
	return false;
}

bool RequestManager::setPostingState(uint8_t state){
	if(this->postState!=state){
		this->postState = state;
		onPostingStateChanged();
		return true;
	}
	return false;
}

void RequestManager::onStateChanged(){
	Action action = {this, getState(), nullptr};
	notifyActionPerformed(action);

	switch(getState()){
		case ST_INITIALIZED:{
			wait(20000);
			timeoutP = millis();
			break;
		}
		case ST_W_CONNECTED:{
			//wait(6000);
			//connectToServer();
			timeoutP = millis();
			break;
		}
		case ST_W_DISCONNECTED:{
			//if(isToBeConnected)
			//	connectToWiFi();
			timeoutP = millis();
			break;
		}
		case ST_W_CONNECTING_FAIL:{
			setState(ST_W_DISCONNECTED);
			timeoutP = millis();
			break;
		}
		case ST_S_CONNECTED:{
			timeoutP = millis();
			break;
		}
		case ST_S_ERROR:{
			wait(30000);
			timeoutP = millis();
			break;
		}
	}

	Serial.print(F("$ Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);
	wait(50);
}

void RequestManager::onPostingStateChanged(){
	Action action = {this, getState(), nullptr};
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
		case ST_P_WAIT_CONTENT_START:{
			timeoutP = millis();
			break;
		}
		case ST_P_WAIT_CONTENT_END:{
			timeoutP = millis();
			break;
		}
		case ST_P_RESPONSE_COMPLETED:{
			onResponseReceived(httpResponse);
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

void RequestManager::postNextRequest(){
	HttpRequest* next = topRequest();
	if(next){
		postRequest(next);
	}
	timeoutP = millis();
}

void RequestManager::postRequest(HttpRequest* httpRequest) {
	if(httpRequest){
		this->httpRequest = httpRequest;

		for(int i=0; i<REQUEST_HEADER_LENGHT; i++)
			request[i] = '0';

		uint8_t size =
				HttpRequestCreator::createRequest(request, httpRequest);

		//onPostRequest(httpRequest);

		//Serial.print(F("AT+CIPSEND="));
		//Serial.println(size);
		delay(2);
		esp->print(F("AT+CIPSEND="));
		esp->println(size);

		Serial.println(F("***   AT SEND"));

		setPostingState(ST_P_POSTING_REQUEST);
		timeoutP = millis();
	}
}

void RequestManager::sendRequest(){
	setPostingState(ST_P_SEND_REQUEST);
	if(httpRequest){
		Serial.println(F("Sending..."));
		Serial.println(request);
		esp->print(request);
	}
	request[0] = '\0';

	Serial.print(F("$ Free RAM = "));
	Serial.println(freeMemory(), DEC);
}

void RequestManager::onResponseReceived(HttpResponse& response){

}

void RequestManager::notifyActionPerformed(Action action){
	IActionListener* listener = getActionListener();
	if(listener!=nullptr){
		listener->actionPerformed(action);
	}
}

void RequestManager::fill(){

}
