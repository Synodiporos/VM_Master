/*
 * RequestManager.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "RequestManager.h"

RequestManager::RequestManager(){
	// TODO Auto-generated constructor stub
	Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);

	initialize();

	//fill();
}

RequestManager::~RequestManager() {
	// TODO Auto-generated destructor stub
}

void RequestManager::initialize(){
	for(int i=0; i<CAPACITY; i++){
		buf[i] = nullptr;
	}

	esp->begin(SRL3_BD);
	esp->println(F("AT"));
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
	esp->println(F("AT+CWMODE=1"));
	timeout = millis();
	setState(ST_INITIALIZING);
}

void RequestManager::connectToWiFi(){
	char at[64];
	sprintf (at, "AT+CWJAP_CUR=\"%s\",\"%s\"",
			WIFI_SSID, WIFI_PASS);

	//Serial.println(at);
	esp->println(at);
	setState(ST_CONNECTING);

	timeout = millis();
}

void RequestManager::checkWiFiConnection(){

}


bool RequestManager::startPosting(){
	if(!posting){
		posting = true;
		return true;
	}
	return false;
}

bool RequestManager::stopPosting(){
	if(posting){
		posting = false;
		return true;
	}
	return false;
}

bool RequestManager::isPosting(){
	return this->posting;
}

void RequestManager::validate(){

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

	if(millis()-time>500){
		//Serial.println(F("R"));
		time = millis();
	}

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
			connectToWiFi();
			break;
		}
		case ST_CONNECTING:{
			if(millis()-timeout>=12000){
				setState(ST_DISCONNECTED);
				//timeout = millis();
			}
			break;
		}
		case ST_CONNECTED:{

			break;
		}
		case ST_DISCONNECTED:{
			if(millis()-timeout>=12000){
				Serial.print(F("Free RAM = "));
				Serial.println(freeMemory(), DEC);
				connectToWiFi();
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


	if (esp->available()){
		while (esp->available() > 0){
			String response = esp->readStringUntil('\n');
			response.trim();
			if(response.length()>0){
				std::string str(response.c_str());
				onEspMessageReceived(str);
			}
		}
	}

}

void RequestManager::fill(){

	for(int i=0; i<35; i++){
		PostSurgeRequest* req = new PostSurgeRequest(i, 0, 0);
		pushRequest(req);
	}
	Serial.println(F("Fill End!"));
	//delay(20);
}

bool RequestManager::setState(uint8_t state){
	if(this->state!=state){
		//Serial.print(F("State: "));
		//Serial.println(state);

		uint8_t old = this->state;
		this->state = state;
		onStateChanged(old);
		return true;
	}
	return false;
}

void RequestManager::onStateChanged(uint8_t oldState){
	this->state = state;
}

bool RequestManager::onPostRequest(HttpRequest* request){

	return false;
}

void RequestManager::onEspMessageReceived(const std::string msg){
	Serial.print(F("Received: "));
	const char* c = msg.c_str();
	Serial.println(c);

	switch(state){
		case ST_OFF:{
			if(msg.compare("OK")==0){
				setState(ST_BLUGED);
			}
			break;
		}
		case ST_INITIALIZING:{
			if(msg.find("AT+CWMODE=1") != std::string::npos){
				setState(ST_INITIALIZED);
			}
			break;
		}
		case ST_INITIALIZED:{

			break;
		}
		case ST_CONNECTING:{
			if(msg.find("WIFI GOT IP") != std::string::npos){
				setState(ST_CONNECTED);
			}
			else if(msg.find("FAIL") != std::string::npos){
				setState(ST_DISCONNECTED);
			}
			break;
		}
		case ST_CONNECTED:{

			break;
		}
	}

	if(msg.find("STATUS:") != std::string::npos){
		char res = msg[7];
		if(res == '2'){
			setState(ST_CONNECTED);
		}
	}


	//delete c;
}

void RequestManager::onResponseReceived(std::string response){

}

void RequestManager::onACKReceived(std::string ack){

}
