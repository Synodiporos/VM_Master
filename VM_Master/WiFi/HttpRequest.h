/*
 * httpRequest.h
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_HTTPREQUEST_H_
#define WIFI_HTTPREQUEST_H_

#include <string>
#include "../System/SystemConstants.h"
using namespace std;

class HttpRequest {
public:
	HttpRequest();
	virtual ~HttpRequest();

	virtual char* getRequest() = 0;
};

#endif /* WIFI_HTTPREQUEST_H_ */
