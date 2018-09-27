/*
 * CharUtil.h
 *
 *  Created on: 9 Μαΐ 2018
 *      Author: Synodiporos
 */

#ifndef CHARUTIL_H_
#define CHARUTIL_H_

#include <Arduino.h>
#include <stdint.h>

#define AT_PREFIX "AT"
#define AT_SEPARATOR '+'
#define AT_END_CMD '='
#define AT_PARAMS_DELIM ','
#define AT_PARSE_LIMIT 32

class CharUtil {
public:

	static uint8_t parse(const char* at,
			String &cmd,
			uint8_t &id,
			char params[3][8]);

	static uint8_t compineAT(char* at, char cmd[3],
			uint8_t id,
			char params[3][8]);

	static void copyCharArray(const char* proto,
			char copy[], uint8_t size);
};

#endif /* CHARUTIL_H_ */
