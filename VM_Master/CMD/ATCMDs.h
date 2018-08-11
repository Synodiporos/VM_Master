/*
 * ATCMDs.h
 *
 *  Created on: 24 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef CMD_ATCMDS_H_
#define CMD_ATCMDS_H_

#include "../System/SystemConstants.h"
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

	static const string AT_ACK;
	static const string AT_HV1;
	static const string AT_SR1;
	static const string AT_HV2;
	static const string AT_SR2;
};

#endif /* CMD_ATCMDS_H_ */
