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

			string com = "";
			auto d = input.begin();
			for (auto it = input.begin()+2;
					it!=input.end(); ++it){
				if(*it=='='){
					ei = n;
					break;
				}
				com += *it;
				n++;
			}

			if(ei>0){
				string s = input.substr(ei+1, input.size()-1);
				int found = s.find(&DELIM);
				if(found!=-1){
					split(s, params);
				}
				else{
					params.push_back(
							input.substr(ei+1, input.size()-1));
				}
			}
			if(com.size()>0){
				command.append( com.substr(1, com.size()-1) );
				//command = com.substr(1, com.size()-1);
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

