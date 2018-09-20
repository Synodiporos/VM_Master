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

#define REQUEST_TYPE_TEST 0
#define REQUEST_TYPE_SURGE 1
#define REQUEST_TYPE_BATTERY 2

#define URL_CONTENT_LENGHT 40

const char psr_content[] PROGMEM = "src=%d&ch=%lu&sl=%d";
const char pbr_content[] PROGMEM = "vin=%d&lv=%d&al=%d";
const char* const formats_of_contents[] PROGMEM =
	{psr_content, pbr_content};


class HttpRequest {
public:
	HttpRequest();
	virtual ~HttpRequest();

	virtual uint8_t getRequestType() = 0;
	virtual uint8_t createRequestContent(char* buffer) = 0;
};

#endif /* WIFI_HTTPREQUEST_H_ */
