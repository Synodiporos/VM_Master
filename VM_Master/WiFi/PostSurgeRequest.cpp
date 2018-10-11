/*
 * PostSurgeRequest.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "PostSurgeRequest.h"
#include <string>
#include <sstream>

PostSurgeRequest::PostSurgeRequest(uint32_t datetime,
			uint8_t source,
			uint32_t charge, uint16_t slope):
			datetime(datetime),
			source(source),
			charge(charge),
			slope(slope){

}

PostSurgeRequest::~PostSurgeRequest() {
	// TODO Auto-generated destructor stub
}

uint8_t PostSurgeRequest::getRequestType(){
	return REQUEST_TYPE_SURGE;
}

uint8_t PostSurgeRequest::createRequestContent(char* buffer){
	char contentFormat[REQUEST_URL_CONTENT_LENGHT];
	strcpy_P(contentFormat,
			(char*)pgm_read_word(&(formats_of_contents[0])));

	uint8_t size = snprintf(buffer, REQUEST_URL_CONTENT_LENGHT,
		contentFormat,
		source, charge, slope);

	buffer[REQUEST_URL_CONTENT_LENGHT-1] = '\0';

	return size;
}
