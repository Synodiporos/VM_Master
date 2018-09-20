/*
 * PostSurgeRequest.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "PostSurgeRequest.h"
#include <string>
#include <sstream>

PostSurgeRequest::PostSurgeRequest(uint8_t source,
			unsigned long charge, unsigned int slope):
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
	/*char content[100];
	strcpy_P(content, (char*)pgm_read_word(&(postRequests[1])));
	char format[128];
	strcpy_P(format, (char*)pgm_read_word(&(postRequests[0])));

	char data[100];
	uint8_t length = snprintf(data, 100,
			content,
			source, charge, slope);

	uint8_t size = getRequestSize();
	snprintf(buffer, size, format,
			WIFI_SURGEROOM_URI, WiFi_SURGE_URI,
			WIFI_SERVER, length, data);


	buffer[size-1] = '\0';*/


	return 0;
}
