/*
 * TestGetRequest.h
 *
 *  Created on: Sep 17, 2018
 *      Author: sgeorgiadis
 */

#ifndef WIFI_GETINFOREQUEST_H_
#define WIFI_GETINFOREQUEST_H_

#include "HttpRequest.h"
#include <stdio.h>
#include <stdlib.h>

class GetInfoRequest: public HttpRequest {
public:
	GetInfoRequest();
	GetInfoRequest(uint8_t id);
	virtual ~GetInfoRequest();

	uint8_t getRequestType();
	uint8_t createRequestContent(char* buffer);

};

#endif /* WIFI_GETINFOREQUEST_H_ */
