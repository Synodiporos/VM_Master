/*
 * httpRequest.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "HttpRequest.h"

HttpRequest::HttpRequest() {
	// TODO Auto-generated constructor stub

}

HttpRequest::~HttpRequest() {
	// TODO Auto-generated destructor stub
}

void HttpRequest::setId(uint8_t id){
	this->id = id;
}

uint8_t HttpRequest::getId(){
	return this->id;
}
