/*
 * httpRequest.h
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_HTTPREQUEST_H_
#define WIFI_HTTPREQUEST_H_

#include "Arduino.h"
#include "../System/SystemConstants.h"
using namespace std;

const char format[] PROGMEM = "GET %s%s?%s HTTP/1.1\r\nHost: %s\r\n\r\n";
const char psr_content[] PROGMEM = "src=%d&ch=%lu&sl=%d&dt=%lu";
const char pbr_content[] PROGMEM = "vin=%d&lv=%d&al=%d";
const char gir_content[] PROGMEM = "id=%d";
const char* const formats_of_contents[] PROGMEM =
	{format, psr_content, pbr_content, gir_content};
#define REQUEST_TYPE_SURGE 1
#define REQUEST_TYPE_BATTERY 2
#define REQUEST_TYPE_INFO 3
#define REQUEST_TYPE_DATETIME 4

class HttpRequest {
public:
	HttpRequest();
	virtual ~HttpRequest();

	void setId(uint8_t id);
	uint8_t getId();

	virtual uint8_t getRequestType() = 0;
	virtual uint8_t createRequestContent(char* buffer) = 0;

private:
	uint8_t id = 0;
};

#endif /* WIFI_HTTPREQUEST_H_ */
