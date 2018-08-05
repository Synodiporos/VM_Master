/*
 * AT.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#ifndef AT_AT_H_
#define AT_AT_H_

#include <vector>
#include <string>
#include "ATCMDs.h"
#include "CMD.h"
#include "CMDErrorReport.h"
#include "CMDBatteryReport.h"
#include "CMDSettings.h"
#include "CMDTestLeds.h"
using namespace std;

#define AT_PREF AT

class AT {
public:
	static const string PREF;
	static const char DELIM;

	virtual ~AT();


	static bool parse(const string& input, string& command, vector<string>& params);
	static CMD* toCMD(const string& at);


private:
	static void split(const string& s, vector<string>& v);
	static long toLong(string str);
};

#endif /* AT_AT_H_ */
