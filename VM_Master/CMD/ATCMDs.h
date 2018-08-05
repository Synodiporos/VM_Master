/*
 * ATCMDs.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_ATCMDS_H_
#define CMD_ATCMDS_H_

#include <string>
using namespace std;

class ATCMDs {
public:
	static const string AT_BT ;
	static const string AT_HV ;
	static const string AT_SETS ;
	static const string AT_SET ;
	static const string AT_TLS ; //Test LEDs
	static const string AT_TBZ ; //Test Buzzer
};

#endif /* CMD_ATCMDS_H_ */
