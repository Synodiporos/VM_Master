/*
 * TestGetRequest.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: sgeorgiadis
 */

#include "TestGetRequest.h"

TestGetRequest::TestGetRequest() {
	// TODO Auto-generated constructor stub

}

TestGetRequest::~TestGetRequest() {
	// TODO Auto-generated destructor stub
}

uint8_t TestGetRequest::getRequestType(){
	return REQUEST_TYPE_TEST;
}

uint8_t TestGetRequest::createRequestContent(char* buffer){
	buffer[0] = '\0';
	return 1;
}
