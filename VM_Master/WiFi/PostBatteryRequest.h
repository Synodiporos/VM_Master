/*
 * PostBatteryRequest.h
 *
 *  Created on: 18 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_POSTBATTERYREQUEST_H_
#define WIFI_POSTBATTERYREQUEST_H_

#include "HttpRequest.h"

#define TE "123456789012345678901234567890"

class PostBatteryRequest: public HttpRequest {
public:
	PostBatteryRequest(unsigned int voltage,
			uint8_t percentage, bool alarm);
	virtual ~PostBatteryRequest();

	char* getRequest();

private:
	unsigned int voltage = 0;
	uint8_t percentage = 0;
	bool alarm = false;
};

#endif /* WIFI_POSTBATTERYREQUEST_H_ */
