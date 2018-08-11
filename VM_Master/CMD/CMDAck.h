/*
 * CMDAck.h
 *
 *  Created on: 9 Αυγ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_CMDACK_H_
#define CMD_CMDACK_H_

#include "CMD.h"
#include "../RFTransceiver/RFTransceiver.h"


class CMDAck: public CMD {
public:
	CMDAck();
	virtual ~CMDAck();
	std::string getName();
	uint8_t onExecute();
	void validate();
};

#endif /* CMD_CMDACK_H_ */
