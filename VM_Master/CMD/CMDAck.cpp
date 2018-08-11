/*
 * CMDAck.cpp
 *
 *  Created on: 9 Αυγ 2018
 *      Author: Synodiporos
 */

#include "CMDAck.h"

CMDAck::CMDAck() {
	// TODO Auto-generated constructor stub

}

CMDAck::~CMDAck() {
	// TODO Auto-generated destructor stub
}

std::string CMDAck::getName(){
	return string("ACK");
}

uint8_t CMDAck::onExecute(){
	char at[RF_PAYLOAD_SIZE];
	char str[] = CMD_ACR;
	sprintf (at, "AT+%s", str);
	RFTransceiver::getInstance()->write(at);
	return RES_COMPLETED;
}

void CMDAck::validate(){

}
