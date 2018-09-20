/*
 * TestGetRequest.h
 *
 *  Created on: Sep 17, 2018
 *      Author: sgeorgiadis
 */

#ifndef WIFI_TESTGETREQUEST_H_
#define WIFI_TESTGETREQUEST_H_

#include "HttpRequest.h"
#include <stdio.h>
#include <stdlib.h>

class TestGetRequest: public HttpRequest {
public:
	TestGetRequest();
	virtual ~TestGetRequest();

	uint8_t getRequestType();
	uint8_t createRequestContent(char* buffer);
};

#endif /* WIFI_TESTGETREQUEST_H_ */
