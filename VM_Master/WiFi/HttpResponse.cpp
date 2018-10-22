/*
 * HttpResponse.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: sgeorgiadis
 */

#include "HttpResponse.h"

HttpResponse::HttpResponse() {
	// TODO Auto-generated constructor stub

}

HttpResponse::HttpResponse(uint16_t http_code, char content[64]):
		http_code(http_code){
	uint8_t size = strlen(content);
	for(int i=0; i<size; i++){
		this->content[i] = content[i];
	}
}

HttpResponse::~HttpResponse() {
	// TODO Auto-generated destructor stub
}

void HttpResponse::setHttpCode(uint16_t code){
	this->http_code = code;
}

void HttpResponse::setContent(char content[64]){
	uint8_t size = strlen(content);
	for(int i=0; i<size; i++){
		this->content[i] = content[i];
	}
	this->lenght = size;
}

void HttpResponse::appendContent(String str){
	uint8_t l = str.length();
	Serial.println(l);
	const char* in = str.c_str();
	uint8_t end = 64-lenght;
	if(l<end)
		end = l;
	for(int i=0; i<end; i++){
		this->content[i+lenght] = in[i];
	}
	this->lenght += end;
	this->content[lenght] = '\0';
	Serial.println(lenght);
}

uint16_t HttpResponse::getHttpCode(){
	return this->http_code;
}

const char* HttpResponse::getContent(){
	return this->content;
}

uint8_t HttpResponse::getLenght(){
	return this->lenght;
}
