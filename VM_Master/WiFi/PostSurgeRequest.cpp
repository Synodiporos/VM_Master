/*
 * PostSurgeRequest.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "PostSurgeRequest.h"

PostSurgeRequest::PostSurgeRequest(uint8_t source,
			unsigned long charge, unsigned int slope):
			HttpRequest(),
			source(source),
			charge(charge),
			slope(slope){

}

PostSurgeRequest::~PostSurgeRequest() {
	// TODO Auto-generated destructor stub
}

char* PostSurgeRequest::getRequest(){
	char content[30];
	strcpy_P(content, (char*)pgm_read_word(&(postRequests[1])));
	char format[129];
	strcpy_P(format, (char*)pgm_read_word(&(postRequests[0])));

	char data[56];
	uint8_t length = snprintf(data, 56, content,
			source, charge, slope);

	char req[208];
	snprintf(req, 208, format,
			WIFI_SURGEROOM_URI, WiFi_SURGE_URI,
			WIFI_SERVER, length, data);

	return req;
}
