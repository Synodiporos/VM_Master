/*
 * CharUtil.cpp
 *
 *  Created on: 9 Μαΐ 2018
 *      Author: Synodiporos
 */

#include "CharUtil.h"


uint8_t CharUtil::parse(const char* at,
			String &cmd,
			uint8_t &id,
			char params[3][8]){

	id = 0;
	String idStr;
	String param;
	uint8_t i = 0;
	uint8_t state = 0;
	char ch = at[i];
	while(ch!='\0' && ch!='\n' && i<AT_PARSE_LIMIT){
		switch(state){
			case 0:{
				if(ch==AT_SEPARATOR)
					state = 1;
				else if(ch != AT_PREFIX[i])
					return 0;
				break;
			}
			case 1:{
				if(ch==AT_SEPARATOR)
					state = 2;
				else if(ch==AT_END_CMD){
					state = 3;
				}
				else
					cmd += ch;
				break;
			}
			case 2:{
				if(ch==AT_END_CMD){
					state = 3;
				}
				else
					idStr += ch;
				break;
			}
			case 3:{
				if(ch==AT_PARAMS_DELIM){
					uint8_t size = param.length();
					if(size>0){
						copyCharArray(param.c_str(), params[0], size);
					}
					param = "";
					state = 4;
				}
				else
					param += ch;
				break;
			}
			case 4:{
				if(ch==AT_PARAMS_DELIM){
					uint8_t size = param.length();
					if(size>0){
						copyCharArray(param.c_str(), params[1], size);
					}
					param = "";
					state = 5;
				}
				else
					param += ch;
				break;
			}
			case 5:{
				if(ch!=AT_PARAMS_DELIM)
					param += ch;
				break;
			}
		}
		i++;
		ch = at[i];
	}

	if(idStr.length()>0)
		id = atoi(idStr.c_str());

	uint8_t size = param.length();
	if(size>0){
		if(state==3){
			copyCharArray(param.c_str(), params[0], size);
		}
		else if(state==4){
			copyCharArray(param.c_str(), params[1], size);
		}
		else{
			copyCharArray(param.c_str(), params[2], size);
		}
	}
	return 1;
}

uint8_t CharUtil::compineAT(char* at, char cmd[3],
				uint8_t id,
				char params[3][8]){

	String res = AT_PREFIX;
	res += AT_SEPARATOR;
	res += cmd;
	if(id>0){
		char idStr[4];
		snprintf(idStr, 4, "%d", id);
		res += AT_SEPARATOR;
		res += String(idStr);
	}

	String paramsStr = "";
	if(params[0]!=0 && params[0][0]!=0){
		paramsStr += params[0];
	}
	if(params[1]!=0 && params[1][0]!=0){
		paramsStr += AT_PARAMS_DELIM;
		paramsStr += params[1];
	}
	if(params[2]!=0 && params[2][0]!=0){
		paramsStr += AT_PARAMS_DELIM;
		paramsStr += params[2];
	}
	if(paramsStr.length()>0){
		res += AT_END_CMD;
		res += paramsStr;
	}
	//at = res.c_str();
	copyCharArray(res.c_str(), at, res.length());
	return 1;
}

void CharUtil::copyCharArray(const char* proto, char copy[], uint8_t size){
//	uint8_t i = 0;
//	char c = proto[i];
//	while(c!=0 && i<size){
//		copy[i] = proto[i];
//		i++;
//		c = proto[i];
//	}
//	copy[i] = 0;
	uint8_t s = strlen(proto)+1;
	snprintf(copy, s, "%s", proto);
	//memcpy(copy, proto, sizeof(proto));
}
