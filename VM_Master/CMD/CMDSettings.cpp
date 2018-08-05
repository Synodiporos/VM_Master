/*
 * CMDSettings.cpp
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "CMDSettings.h"

CMDSettings::CMDSettings() {
	// TODO Auto-generated constructor stub

}

CMDSettings::CMDSettings(std::vector<string>& params) {
	// TODO Auto-generated constructor stub

}

CMDSettings::~CMDSettings() {
	// TODO Auto-generated destructor stub
}

string CMDSettings::getName(){
	return "SE";
}

uint8_t CMDSettings::onExecute(){
	return RES_COMPLETED;
}

void CMDSettings::validate(){
	CMD::validate();
}
