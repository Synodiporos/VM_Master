/*
 * SerialBroadcaster.h
 *
 *  Created on: 21 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_SERIALBROADCASTER_H_
#define SYSTEM_SERIALBROADCASTER_H_

#include "../CMD/CMD.h"
#include "../CMD/AT.h"
#include "../RFTransceiver/RFTransceiver.h"

class SerialBroadcaster {
public:
	virtual ~SerialBroadcaster();
	static SerialBroadcaster* getInstance();
	void validate();

private:
	SerialBroadcaster();
	static SerialBroadcaster* instance;
	string inputString;

	void onSerialMessageReceived(const string msg);
};

#endif /* SYSTEM_SERIALBROADCASTER_H_ */
