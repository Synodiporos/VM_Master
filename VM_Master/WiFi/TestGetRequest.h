/*
 * TestGetRequest.h
 *
 *  Created on: Sep 17, 2018
 *      Author: sgeorgiadis
 */

#ifndef WIFI_TESTGETREQUEST_H_
#define WIFI_TESTGETREQUEST_H_

#include "HttpRequest.h"

#define POST_HTTP_REQUEST "GET %s%s HTTP/1.1\r\nHost: %s\r\n\r\n"

class TestGetRequest: public HttpRequest {
public:
	TestGetRequest();
	virtual ~TestGetRequest();

	char* getRequest();

};

#endif /* WIFI_TESTGETREQUEST_H_ */
