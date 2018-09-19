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

char* TestGetRequest::getRequest(){
	char server[] = WIFI_SERVER;
	char uri[] = WIFI_SURGEROOM_URI;
	char test_uri[] = WiFi_TEST_URI;

	//char currentRequest[] = std::string("GET ");
	//currentRequest += uri + " HTTP/1.1\r\n" +
	//		"Host: " + server + "\r\n\r\n" ;
	//"Accept: *" + "/" + "*\r\n" +
	//"Content-Length: " + data.length() + "\r\n" ;
	//"Content-Type: application/x-www-form-urlencoded\r\n" +
	//"\r\n" + data;

	char req[72];
	sprintf (req, POST_HTTP_REQUEST,
			uri, test_uri, server);
	return req;
}
