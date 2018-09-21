/*
 * HttpRequestCreator.cpp
 *
 *  Created on: Sep 20, 2018
 *      Author: sgeorgiadis
 */

#include "HttpRequestCreator.h"

HttpRequestCreator::HttpRequestCreator() {
	// TODO Auto-generated constructor stub

}

HttpRequestCreator::~HttpRequestCreator() {
	// TODO Auto-generated destructor stub
}

String HttpRequestCreator::createRequest(HttpRequest* request){
	/*String res = "GET ";
	res += WIFI_SURGEROOM_URI;
	res += WiFi_TEST_URI;
	res += "HTTP/1.1\r\n";
	res += "Host: ";
	res += WIFI_SERVER;
	res += "\r\n\r\n";*/

	String res;
	return res;
}

uint8_t HttpRequestCreator::createRequest(char* buffer,
		HttpRequest* request){
	if(!request)
		return 0;

	char data[REQUEST_URL_CONTENT_LENGHT];
	uint8_t sc = request->createRequestContent(data);

	int requestType = request->getRequestType();
	char * uri = nullptr;
	switch(requestType){
		case REQUEST_TYPE_SURGE:{
			uri = WiFi_SURGE_URI;
			break;
		}
		case REQUEST_TYPE_BATTERY:{
			uri = WiFi_BATTERY_URI;
			break;
		}
		case REQUEST_TYPE_TEST:{
			uri = WiFi_TEST_URI;
			break;
		}
	}

	uint8_t size = WIFI_REQUEST_LENGHT;
	char urlFormat0[size];
		strcpy_P(urlFormat0,
				(char*)pgm_read_word(&(formats_of_contents[2])));

	char urlFormat[] = "GET %s%s?%s HTTP/1.1\r\nHost: %s\r\n\r\n";
	uint8_t lenght = snprintf(buffer, size, urlFormat,
			WIFI_SURGEROOM_URI, uri, data,
			WIFI_SERVER, sc, data);
	buffer[size-1] = '\0';
	return lenght;
}
