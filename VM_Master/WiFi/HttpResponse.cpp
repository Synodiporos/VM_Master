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

HttpResponse::HttpResponse(uint16_t http_code, uint8_t content_type,
			uint16_t content_lenght, const char content[]):
		http_code(http_code),
		content_type(content_type),
		content_lenght(content_lenght),
		content(content){

}

HttpResponse::~HttpResponse() {
	// TODO Auto-generated destructor stub
}

void HttpResponse::setHttpCode(uint16_t code){
	this->http_code = code;
}

void HttpResponse::setContentType(uint8_t type){
	this->content_type = type;
}

void HttpResponse::setContentLenght(uint16_t lenght){
	this->content_lenght = lenght;
}

void HttpResponse::setContent(char content[]){
	this->content = content;
}

uint16_t HttpResponse::getHttpCode(){
	return this->http_code;
}

uint8_t HttpResponse::getContentType(){
	return this->content_type;
}

uint16_t HttpResponse::getContentLenght(){
	return this->content_lenght;
}

const char* HttpResponse::getContent(){
	return this->content;
}
