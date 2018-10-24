/*
 * TestGetRequest.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: sgeorgiadis
 */

#include "GetInfoRequest.h"

GetInfoRequest::GetInfoRequest() {
	// TODO Auto-generated constructor stub

}

GetInfoRequest::GetInfoRequest(uint8_t id) {
	// TODO Auto-generated constructor stub
	setId(id);
}

GetInfoRequest::~GetInfoRequest() {
	// TODO Auto-generated destructor stub
}

uint8_t GetInfoRequest::getRequestType(){
	return REQUEST_TYPE_INFO;
}

uint8_t GetInfoRequest::createRequestContent(char* buffer){
	char contentFormat[REQUEST_URL_PARAMS_LENGHT];
	strcpy_P(contentFormat,
			(char*)pgm_read_word(&(formats_of_contents[3])));

	uint8_t size = snprintf(buffer, REQUEST_URL_PARAMS_LENGHT,
		contentFormat, getId());

	buffer[size] = '\0';

	//buffer[0] = '\0';
	return size;
}
