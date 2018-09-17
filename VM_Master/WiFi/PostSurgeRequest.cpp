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
	char at[40];
	uint8_t length = snprintf(at, 40, POST_SURGE_REQUEST_DATA,
			source, charge, slope);

	char server[] = WIFI_SERVER;
	char uri[] = WIFI_SURGEROOM_URI;
	char surge_uri[] = WiFi_SURGE_URI;

	//char currentRequest[] = std::string("GET ");
	//currentRequest += uri + " HTTP/1.1\r\n" +
	//		"Host: " + server + "\r\n\r\n" ;
	//"Accept: *" + "/" + "*\r\n" +
	//"Content-Length: " + data.length() + "\r\n" ;
	//"Content-Type: application/x-www-form-urlencoded\r\n" +
	//"\r\n" + data;

	char req[192];
	snprintf(req, 192, POST_SURGE_REQUEST,
			uri, surge_uri, server, length, at);

	return req;
}
