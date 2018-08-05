/*
 * CMDTestLeds.h
 *
 *  Created on: 28 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDTESTLEDS_H_
#define CMD_CMDTESTLEDS_H_
#include <Arduino.h>
#include <string>
using namespace std;
#include "CMD.h"
#include "../System/SystemConstants.h"

#define TEST_INTERVAL 2000

class CMDTestLeds: public CMD {
public:
	CMDTestLeds();
	virtual ~CMDTestLeds();
	virtual string getName();
	virtual uint8_t onExecute();
	void validate();

private:
	unsigned long time = 0;
	uint8_t led = 0;
};

#endif /* CMD_CMDTESTLEDS_H_ */
