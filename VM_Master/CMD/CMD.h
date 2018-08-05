/*
 * CMD.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef CMD_CMD_H_
#define CMD_CMD_H_
#include <string>
#include <vector>
#include <stdint.h>
using namespace std;
#include "../Commons/IStateListener.h"
#include "CMDExecutor.h"

#define SYSTEM 0
#define SRL 1
#define RF 2
#define ESP 3
#define RES_ERROR 0
#define RES_COMPLETED 1
#define RES_ONPROGRESS 2
#define RES_WRONGPARAMS 3
#define STATE_STOPED 0
#define STATE_EXECUTED 1
#define STATE_ONPROGRESS 2
#define STATE_COMPLETED 3

class CMD {
public:
	CMD();
	CMD(std::vector<string>& params);
	virtual ~CMD();

	unsigned int getId();
	virtual std::string getName();
	virtual void setParams(std::vector<string>& params);
	virtual std::vector<string>& getParams();
	void setSource(uint8_t source);
	uint8_t getSource();
	uint8_t getState();
	virtual bool isExecuted();
	uint8_t execute();
	virtual void validate();

	void print();

protected:
	uint8_t source = 0;

	virtual bool setState(uint8_t state);
	virtual uint8_t onExecute() = 0;
	virtual void onCompleted();
	virtual void onError(const uint8_t error);
	virtual void onStateChanged(uint8_t state);

private:
	std::vector<string> params;
	uint8_t state = STATE_STOPED;
	static unsigned int idCount;
	unsigned int id;
};

#endif /* CMD_CMD_H_ */
