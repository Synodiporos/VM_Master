/*
 * CMDStartUp.h
 *
 *  Created on: 30 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDSTARTUP_H_
#define CMD_CMDSTARTUP_H_

#include "Arduino.h"
#include "../System/SystemConstants.h"
#include "CMD.h"
#include "../Timer/Timer.h"

#define STARTUP_INTERVAL 500

class CMDStartUp: public CMD {
public:
	CMDStartUp();
	virtual ~CMDStartUp();
	std::string getName();
	uint8_t onExecute();
	void validate();

private:
	unsigned long time = 0;
};

#endif /* CMD_CMDSTARTUP_H_ */
