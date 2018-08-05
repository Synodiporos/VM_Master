/*
 * CMDBatteryReport.cpp
 *
 *  Created on: 23 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "../CMD/CMDBatteryReport.h"

CMDBatteryReport::CMDBatteryReport() : CMD(){
	// TODO Auto-generated constructor stub

}

CMDBatteryReport::CMDBatteryReport(std::vector<string>& params) :
	CMD(params){

}

CMDBatteryReport::~CMDBatteryReport() {
	// TODO Auto-generated destructor stub
}

string CMDBatteryReport::getName(){
	return "BT";
}

uint8_t CMDBatteryReport::onExecute(){
	return RES_COMPLETED;
}

void CMDBatteryReport::validate(){
	CMD::validate();
}
