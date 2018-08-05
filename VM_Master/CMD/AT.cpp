/*
 * AT.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "Arduino.h"
#include "../CMD/AT.h"

const string AT::PREF = "AT";
const char AT::DELIM = ',';

AT::~AT() {
	// TODO Auto-generated destructor stub
}

bool AT::parse(const std::string& input,
		std::string& command, vector<string>& params){

	if(std::equal(PREF.begin(), PREF.end(), input.begin())){
		unsigned int n = PREF.size();
		unsigned int ei = 0;

		for(char c : input) {
			if(c=='='){
				ei = n;
				break;
			}
			else if(c=='\r')
				break;
			command.push_back(c);
			n++;
		}

		/*std::vector<char>::iterator it = input.begin();
		for(it;
				it != input.end(); ++it) {
			if(*it=='='){
				ei = n;
				break;
			}
			else if(*it=='\r')
				break;
			command.push_back(*it);
			n++;

			//Serial.println(*it);
		}*/
		if(ei>0){
			string s = input.substr(ei+1, input.size()-1);
			int found = s.find(&DELIM);
		}
		return true;
	}
	else{
		// NO AT COMMAND
		return false;
	}
}

CMD* AT::toCMD(const std::string& at){
	std::string command = "";
	vector<string> params;
	CMD* cmd = nullptr;
	bool res = parse(at, command, params);

	//Serial.println(command.c_str());
	if(res){
		//string& s = ATCommands::AT_BT;
		if(command.compare(ATCMDs::AT_BT)==0){
			cmd = new CMDBatteryReport(params);
		}
		else if(command.compare(ATCMDs::AT_SET)==0){
			cmd = new CMDSettings(params);
			cmd->setParams(params);
		}
		else if(command.compare(ATCMDs::AT_TLS)==0){
			cmd = new CMDTestLeds();
		}
		else if(command.compare(ATCMDs::AT_TBZ)==0){

		}
		else{
			cmd = new CMDErrorReport('1');
		}
	}
	else
		cmd = new CMDErrorReport();
	return cmd;
}

void AT::split(const std::string& s, vector<string>& v) {
    auto i = 0;
    auto pos = s.find(DELIM);
    while (pos != string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(DELIM, pos);

      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
}

long AT::toLong(const std::string str){
	return atol(str.c_str());
}

/*void AT::print(){
	cout << "AT[" << command << " params:" ;
	for(std::vector<string>::iterator it = params.begin();
			it != params.end(); ++it) {
		cout << *it ;
		if(it!=params.end()-1)
			cout << " ";
	}
	cout << "]" << endl;
}*/

