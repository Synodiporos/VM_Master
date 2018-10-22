/*
 * HttpResponse.h
 *
 *  Created on: Oct 11, 2018
 *      Author: sgeorgiadis
 */

#ifndef WIFI_HTTPRESPONSE_H_
#define WIFI_HTTPRESPONSE_H_

#include <Arduino.h>
#include <stdint.h>
//using namespace std;

class HttpResponse {
public:
	HttpResponse();
	HttpResponse(uint16_t http_code, char content[64]);
	virtual ~HttpResponse();

	void setHttpCode(uint16_t code);
	void setContent(char content[]);
	void appendContent(String str);

	uint16_t getHttpCode();
	const char* getContent();
	uint8_t getLenght();

private:
	uint16_t http_code = 404;
	char content[64];
	uint8_t lenght = 0;
};

#endif /* WIFI_HTTPRESPONSE_H_ */
