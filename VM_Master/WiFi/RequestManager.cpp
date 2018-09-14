/*
 * RequestManager.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "RequestManager.h"

static RequestManager* RequestManager::instance = nullptr;

RequestManager::RequestManager(){
	// TODO Auto-generated constructor stub
	Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);

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
	esp->println(F("AT+CWMODE=3"));
	//esp->println(F("AT"));
	timeout = millis();
	setState(ST_INITIALIZING);
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

void RequestManager::checkWiFiConnection(){
	setState(ST_W_CHECK);
	//Serial.println(F("AT+CWJAP?"));
	//esp->println("AT+CWJAP?");
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

bool RequestManager::startPosting(){
	if(!posting){
		posting = 1;
		return true;
	}
	return false;
}

bool RequestManager::stopPosting(){
	if(posting){
		posting = 0;
		return true;
	}
	return false;
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

bool RequestManager::isPosting(){
	return this->posting;
}

void RequestManager::validate(){
	/*if(millis()-time>500){
		Serial.println(F("R"));
		time = millis();
	}*/

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

	/*if(millis()-time>500){
		if(cc<5){
			cc++;
			HttpRequest* req = popRequest();
			if(req){
				std::string str = req->getRequest();
				Serial.println(str.c_str());
				delay(10);
				delete req;
			}
		}
		else{
			Serial.println();
			//fill();
			PostSurgeRequest* req = new PostSurgeRequest(16, 1, 0);
			pushRequest(req);
			PostSurgeRequest* req2 = new PostSurgeRequest(17, 2, 0);
			pushRequest(req2);
			cc = 0;
			delay(1000);
			Serial.println();
		}
		time = millis();
	}*/

	switch(state){
		case ST_OFF:{
			initializeModule();
			break;
		}
		case ST_INITIALIZING:{
			if(millis()-timeout>2000){
				initializeModule();
				timeout = millis();
			}
			break;
		}
		case ST_INITIALIZED:{
			//checkWiFiConnection();
			//wait();
			//initializeModule();
			connectToWiFi();
			break;
		}
		case ST_W_CHECK:{
			if(millis()-timeout>4000){
				setState(ST_W_DISCONNECTED);
				timeout = millis();
			}
			break;
		}
		case ST_W_CONNECTING:{
			if(millis()-timeout>=12000){
				setState(ST_W_DISCONNECTED);
				//timeout = millis();
			}
			break;
		}
		case ST_W_CONNECTED:{
			//connectToServer();
			//checkServerConnection();
			connectToServer();
			break;
		}
		case ST_W_DISCONNECTED:{
			if(millis()-timeout>=12000){
				connectToWiFi();
			}
			break;
		}
		case ST_S_CHECK:{
			//connectToServer();
			if(millis()-timeout>=3000){
				setState(ST_S_DISCONNECTED);
				timeout = millis();
			}
			break;
		}
		case ST_S_CONNECTING:{
			if(millis()-timeout>=10000){
				setState(ST_S_DISCONNECTED);
			}
			break;
		}
		case ST_S_CONNECTED:{
			if(millis()-timeout>=WIFI_CHECK_INTERVAL){
				checkWiFiConnection();
			}
			break;
		}
		case ST_S_DISCONNECTED:{
			if(millis()-timeout>=4000){
				connectToServer();
			}
			break;
		}
	}

	if(isPosting()){
		if(size()>0){
			if(state!=POSTING){
				onPostRequest(topRequest());
				//state = POSTING;
			}

			if(millis()-time>500){

			}
		}
	}

	switch(posting){
		case ST_P_STOP_POSTING:{
			break;
		}
		case ST_P_POSTING:{
			break;
		}
		case ST_P_POST_REQUEST:{
			break;
		}
		case ST_P_SEND_REQUEST:{
			break;
		}
	}

	if (esp->available()){
		while (esp->available() > 0 ){
			//Serial.println(F("-"));
			String response = esp->readStringUntil('\n');
			response.trim();
			if(response.length()>0){
				std::string str(response.c_str());
				onEspMessageReceived(str);
			}
			//Serial.println(F("+"));
		}
	}

	/*std::string input;
	if (esp->available()){
		uint8_t c = 64;
		while (esp->available() > 0 && c>0){
			char inChar = (char)esp->read();
			input += inChar;
			if (inChar == '\n' || inChar == '\r')
				onEspMessageReceived(input);

			c--;
			if(c==1){
				input =+ '\n';
				onEspMessageReceived(input);
			}
		}
	}*/
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

void RequestManager::onStateChanged(uint8_t oldState){
	//Serial.print(F("State: "));
	//Serial.println(state);


	std::string data;
	Action action(this, state, nullptr, &data);
	notifyActionPerformed(action);

	if(state==ST_W_DISCONNECTED){
		connectToWiFi();
	}
	if(state==ST_S_CONNECTED){
		postRequest();
	}
	wait(2000);
}

void RequestManager::onEspMessageReceived(const std::string msg){
	//Serial.print(F("-- Received: "));
	//const char* c = msg.c_str();
	//Serial.println(c);

	switch(state){
		case ST_OFF:{
			if(msg.compare(ST_RESP_OK)==0){
				setState(ST_BLUGED);
			}
			break;
		}
		case ST_INITIALIZING:{
			if(msg.compare(ST_RESP_OK)==0){
				setState(ST_INITIALIZED);
			}
			break;
		}
		case ST_INITIALIZED:{

			break;
		}
		case ST_W_CHECK:{
			if(msg.compare(ST_RESP_OK)==0){
				if(help=='O')
					setState(ST_W_CONNECTED);
				else
					setState(ST_W_DISCONNECTED);
			}
			if(msg.find("+CWJAP:") != std::string::npos){
				if(msg.find(WIFI_SSID) != std::string::npos){
					help = 'O';
				}
				else{
					help = 'F';
				}
			}
			else if(msg.find("No AP:") != std::string::npos){
				setState(ST_W_DISCONNECTED);
				connectToWiFi();
			}
			break;
		}
		case ST_W_CONNECTING:{
			if(msg.compare(ST_RESP_OK)==0){
				setState(ST_W_CONNECTED);
			}
			else if(msg.find("FAIL") != std::string::npos){
				setState(ST_W_DISCONNECTED);
			}
			break;
		}
		case ST_W_CONNECTED:{

			break;
		}
		case ST_S_CHECK:{
			if(msg.compare(ST_RESP_OK)==0){
				if(help == '2' || help == '3'){
					setState(ST_S_CONNECTED);
				}
				else{
					setState(ST_S_DISCONNECTED);
					connectToServer();
				}
			}
			if(msg.compare("STATUS:2") == 0){
				help = '2';
			}
			else if(msg.compare("STATUS:3") == 0){
				help = '3';
			}
			break;
		}
		case ST_S_CONNECTING:{
			if(msg.compare(ST_RESP_OK) == 0){
				setState(ST_S_CONNECTED);
			}
			else if(msg.compare("CLOSED") == 0){
				setState(ST_S_DISCONNECTED);
			}
			else if(msg.find(" CONN") != std::string::npos){
				help = 24;
			}
			if(help==24 && msg.compare("ERROR")){
				setState(ST_S_CONNECTED);
			}
			break;
		}
		case ST_S_CONNECTED:{

			break;
		}
		case ST_S_DISCONNECTED:{

			break;
		}
	}

	switch(posting){
		case ST_P_STOP_POSTING:{
			break;
		}
		case ST_P_POSTING:{
			break;
		}
		case ST_P_POST_REQUEST:{
			if(msg.compare(">") == 0) {
				sendRequest();
			}
			break;
		}
		case ST_P_SEND_REQUEST:{
			if(msg.compare("SEND OK") == 0) {
				while (esp->available()) {
					String tmpResp = esp->readString();
					std::string resp(tmpResp.c_str());
					onResponseReceived(resp);
				}

			}
			break;
		}
	}
	//delay(50);
	//delete c;
}

void RequestManager::postRequest() {
	std::string data; //data for the POST request
	std::string server = WIFI_SERVER;
	std::string uri = WiFi_TEST_URI;

	currentRequest = std::string("GET ");
	currentRequest += uri + " HTTP/1.1\r\n" +
			"Host: " + server + "\r\n\r\n" ;
	//"Accept: *" + "/" + "*\r\n" +
	//"Content-Length: " + data.length() + "\r\n" ;
	//"Content-Type: application/x-www-form-urlencoded\r\n" +
	//"\r\n" + data;

	Serial.println(F("GET Request text: "));

	String sendCmd = "AT+CIPSEND="; //determine the number of caracters to be sent.
	esp->print(sendCmd);
	esp->println(currentRequest.length()-0);

	posting = ST_P_POST_REQUEST;
	/*

	if(esp->find(">")) {
		Serial.println("Sending..");
		esp->print(postRequest);

		Serial.println("Data to send: ");
		Serial.println(data);
		Serial.print("Data length: ");
		Serial.println(data.length());
		Serial.print("Request length: ");
		Serial.println(postRequest.length());
		Serial.println("Request Sent:");
		Serial.println(postRequest);

		if( esp->find("SEND OK")) {
			Serial.println("Packet sent");
			while (esp->available()) {
				String tmpResp = esp->readString();
				Serial.println(tmpResp);
			}

			// close the connection
			esp->println("AT+CIPCLOSE");
		}
	}*/
}

void RequestManager::onPostRequest(HttpRequest* request){

}

void RequestManager::onGetRequest(HttpRequest* request){

}

void RequestManager::sendRequest(){
	this->posting = ST_P_SEND_REQUEST;
	Serial.println(F("Sending..."));
	Serial.println(currentRequest.c_str());
	esp->print(currentRequest.c_str());
	currentRequest.empty();
}

void RequestManager::onResponseReceived(std::string response){

}

void RequestManager::onACKReceived(std::string ack){

}

void RequestManager::notifyActionPerformed(Action action){
	IActionListener* listener = getActionListener();
	if(listener!=nullptr){
		listener->actionPerformed(action);
	}
}

