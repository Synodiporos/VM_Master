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

uint8_t PostBatteryRequest::getRequestType(){
	return REQUEST_TYPE_BATTERY;
}

uint8_t PostBatteryRequest::createRequestContent(char* buffer){
	char contentFormat[REQUEST_URL_PARAMS_LENGHT];
	strcpy_P(contentFormat,
			(char*)pgm_read_word(&(formats_of_contents[2])));

	uint8_t size = snprintf(buffer, REQUEST_URL_PARAMS_LENGHT,
			contentFormat,
			voltage, percentage, alarm);

	buffer[REQUEST_URL_PARAMS_LENGHT-1] = '\0';

	return size;
}
