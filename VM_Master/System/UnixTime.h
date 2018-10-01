/*
 * UnixTime.h
 *
 *  Created on: 28 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_UNIXTIME_H_
#define SYSTEM_UNIXTIME_H_

#include <Arduino.h>

class UnixTime {
public:
	virtual ~UnixTime();
	static void setUnixTime(unsigned long time);
	static unsigned long getUnixTime();
	static bool isUnixTimeSet();

private:
	UnixTime();
	static unsigned long unixTime;
	static unsigned long timeSet;

};

#endif /* SYSTEM_UNIXTIME_H_ */
