/*
 * UnixTime.cpp
 *
 *  Created on: 28 Σεπ 2018
 *      Author: Synodiporos
 */

#include "UnixTime.h"

unsigned long UnixTime::unixTime = 0;
unsigned long UnixTime::timeSet = 0;

UnixTime::UnixTime() {
	// TODO Auto-generated constructor stub

}

UnixTime::~UnixTime() {
	// TODO Auto-generated destructor stub
}

void UnixTime::setUnixTime(unsigned long time){
	timeSet = (uint32_t)(millis()/1000);
	unixTime = time;
}

unsigned long UnixTime::getUnixTime(){
	if(isUnixTimeSet()){
		unsigned long seconds =
				unixTime + (uint32_t)(millis()/1000) - timeSet;
		return seconds;
	}
	return 0;
}

static bool UnixTime::isUnixTimeSet(){
	return timeSet>0;
}
