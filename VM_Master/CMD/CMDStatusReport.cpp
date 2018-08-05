/*
 * CMDStatusReport.cpp
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "../CMD/CMDStatusReport.h"

CMDStatusReport::CMDStatusReport() {
	// TODO Auto-generated constructor stub

}

CMDStatusReport::~CMDStatusReport() {
	// TODO Auto-generated destructor stub
}

uint8_t CMDStatusReport::onExecute(){
	return RES_COMPLETED;
}

void CMDStatusReport::validate(){
	CMD::validate();
}
