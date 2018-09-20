/*
 * HttpRequestCreator.h
 *
 *  Created on: Sep 20, 2018
 *      Author: sgeorgiadis
 */

#ifndef WIFI_HTTPREQUESTCREATOR_H_
#define WIFI_HTTPREQUESTCREATOR_H_

#include <Arduino.h>
#include "HttpRequest.h"
#include "../System/SystemConstants.h"
#include "HttpRequest.h"

#define URL_REQUEST_LENGHT 128
const char format[] PROGMEM = "GET %s%s HTTP/1.1\r\nHost: %s\r\n\r\n";
const char* const RFL[] PROGMEM = {format};


class HttpRequestCreator {
public:
	HttpRequestCreator();
	virtual ~HttpRequestCreator();

	static String createRequest(HttpRequest* request);
	static uint8_t createRequest(char* buffer, HttpRequest* request);
};

#endif /* WIFI_HTTPREQUESTCREATOR_H_ */
