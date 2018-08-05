/*
 * CMDErrorReport.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDERRORREPORT_H_
#define CMD_CMDERRORREPORT_H_
#include "../CMD/CMD.h"

class CMDErrorReport : public CMD{
public:
	CMDErrorReport();
	CMDErrorReport(char code);
	virtual ~CMDErrorReport();
	string getName();
	void setErrorCode(char code);
	uint8_t onExecute();
	void validate();
	void print();

	string st;
};

#endif /* CMD_CMDERRORREPORT_H_ */
