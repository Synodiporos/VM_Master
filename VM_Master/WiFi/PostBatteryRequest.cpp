/*
 * PostBatteryRequest.cpp
 *
 *  Created on: 18 Σεπ 2018
 *      Author: Synodiporos
 */

#include "PostBatteryRequest.h"

PostBatteryRequest::PostBatteryRequest(unsigned int voltage,
		uint8_t percentage, bool alarm) :
		voltage(voltage),
		percentage(percentage),
		alarm(alarm){
	// TODO Auto-generated constructor stub

}

PostBatteryRequest::~PostBatteryRequest() {
	// TODO Auto-generated destructor stub
}

char* PostBatteryRequest::getRequest(){
	char content[27];
	strcpy_P(content, (char*)pgm_read_word(&(postRequests[2])));
	char format[129];
	strcpy_P(format, (char*)pgm_read_word(&(postRequests[0])));

	char data[40];
	uint8_t length = snprintf(data, 40,
			content,
			voltage, percentage, alarm);


	char req[192];
	snprintf(req, 192, format,
			WIFI_SURGEROOM_URI, WiFi_BATTERY_URI,
			WIFI_SERVER, length, data);

	return req;
}
