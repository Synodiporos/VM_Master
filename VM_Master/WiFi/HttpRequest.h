/*
 * httpRequest.h
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_HTTPREQUEST_H_
#define WIFI_HTTPREQUEST_H_

#include "Arduino.h"
#include <string>
#include "../System/SystemConstants.h"
using namespace std;

const char pr_format[] PROGMEM = "POST %s%s HTTP/1.1\r\nHost: %s\r\nAccept: */*\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s";
const char psr_content[] PROGMEM = "source=%d&charge=%lu&slope=%d";
const char pbr_content[] PROGMEM = "volts=%d&level=%d&alarm=%d";
const char* const postRequests[] PROGMEM = {pr_format, psr_content, pbr_content};

class HttpRequest {
public:
	HttpRequest();
	virtual ~HttpRequest();

	virtual char* getRequest() = 0;
};

#endif /* WIFI_HTTPREQUEST_H_ */
