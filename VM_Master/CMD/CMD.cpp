/*
 * CMD.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: sgeorgiadis
 */

#include "../CMD/CMD.h"
using namespace std;
#include "Arduino.h"

unsigned int CMD::idCount = 0;

CMD::CMD() : id(++idCount){
}

CMD::CMD(std::vector<string>& params)
	:id(++idCount){
	setParams(params);
}

CMD::~CMD() {
	// TODO Auto-generated destructor stub
}

unsigned int CMD::getId(){
	return this->id;
}

string CMD::getName(){
	return "?";
}

void CMD::setParams(vector<string>& params){
	this->params.clear();
	for(std::vector<string>::iterator it = params.begin();
					it != params.end(); ++it) {
		this->params.push_back(*it);
	}
}

vector<string>& CMD::getParams(){
	return this->params;
}

void CMD::setSource(uint8_t source){
	this->source = source;
}

uint8_t CMD::getSource(){
	return this->source;
}

bool CMD::setState(uint8_t state){
	if(this->state!=state){
		this->state = state;
		onStateChanged(state);
		return true;
	}
	return false;
}

uint8_t CMD::getState(){
	return this->state;
}

bool CMD::isExecuted(){
	uint8_t st = getState();
	return st==STATE_ONPROGRESS
			|| st==STATE_EXECUTED;
}

void CMD::print(){
	Serial.print(F("CMD "));
	Serial.print(getName().c_str());
	Serial.print(F(" id:"));
	Serial.print(getId());
	Serial.print(F(" source:"));
	Serial.print(getSource());
	Serial.print(F(" params:["));

	vector<string> p = getParams();
	for(std::vector<string>::iterator it = p.begin();
				it != p.end(); ++it) {
		Serial.print( ((string)*it).c_str() );
		if(it!=p.end()-1)
			Serial.print(F( ", "));
	}
	Serial.println(F( "]" ));
}

uint8_t CMD::execute(){
	Serial.print(F("Execute "));
	this->print();
	this->setState(STATE_EXECUTED);
	uint8_t res = onExecute();
	if(res==RES_ONPROGRESS)
		CMDExecutor::getInstance()->pushCMD(this);
	else if(res==RES_COMPLETED)
		onCompleted();
	else
		onError(RES_WRONGPARAMS);

	return res;
}

void CMD::validate(){

}

//Called by concrete CMDs
void CMD::onCompleted(){
	setState(STATE_COMPLETED);
	CMDExecutor::getInstance()->removeCMD(this);
}

void CMD::onError(const uint8_t error){

}

void CMD::onStateChanged(uint8_t state){

}

