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

	char data[40];
	uint8_t sc = request->createRequestContent(data);

	Serial.print("Content: ");
	Serial.println(sc);


	char urlFormat[] = "GET %s%s?%s HTTP/1.1\r\nHost: %s\r\n\r\n";
	uint8_t size = URL_REQUEST_LENGHT;
	snprintf(buffer, size, urlFormat,
			WIFI_SURGEROOM_URI, WiFi_BATTERY_URI, data,
			WIFI_SERVER, sc, data);
	buffer[size-1] = '\0';

	return strlen(buffer);;
}
