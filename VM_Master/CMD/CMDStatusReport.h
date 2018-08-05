/*
 * CMDStatusReport.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDSTATUSREPORT_H_
#define CMD_CMDSTATUSREPORT_H_

#include "../CMD/CMD.h"

class CMDStatusReport: public CMD {
public:
	CMDStatusReport();
	virtual ~CMDStatusReport();
	uint8_t onExecute();
	void validate();
};

#endif /* CMD_CMDSTATUSREPORT_H_ */
