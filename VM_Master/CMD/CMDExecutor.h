/*
 * CMDExecutor.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef CMD_CMDEXECUTOR_H_
#define CMD_CMDEXECUTOR_H_

#include <vector>
using namespace std;
#include "../CMD/CMD.h"
#include "../Commons/IStateListener.h"

class CMD;

class CMDExecutor {
public:

	virtual ~CMDExecutor();
	static CMDExecutor* getInstance();
	bool pushCMD(CMD* cmd);
	bool removeCMD(CMD* cmd);
	bool isEmpty();
	void clear();
	void validate();


private:
	std::vector<CMD*> vector;
	static CMDExecutor* instance;
	CMDExecutor();
	void begin();
};

#endif /* CMD_CMDEXECUTOR_H_ */
