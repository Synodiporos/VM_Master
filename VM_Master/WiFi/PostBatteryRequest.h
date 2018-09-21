/*
 * PostBatteryRequest.h
 *
 *  Created on: 18 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_POSTBATTERYREQUEST_H_
#define WIFI_POSTBATTERYREQUEST_H_

#include "HttpRequest.h"

class PostBatteryRequest: public HttpRequest {
public:
	PostBatteryRequest(unsigned int voltage,
			uint8_t percentage, bool alarm);
	virtual ~PostBatteryRequest();

	uint8_t getRequestType();
	uint8_t createRequestContent(char* buffer);

private:
	unsigned int voltage = 0;
	uint8_t percentage = 0;
	bool alarm = false;
};

#endif /* WIFI_POSTBATTERYREQUEST_H_ */
