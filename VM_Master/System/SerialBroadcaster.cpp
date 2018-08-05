/*
 * SerialBroadcaster.cpp
 *
 *  Created on: 21 Ιουλ 2018
 *      Author: Synodiporos
 */
#include "Arduino.h"
#include "SerialBroadcaster.h"
#include "../Memory/MemoryFree.h"
#include "../Memory/pgmStrToRAM.h"

SerialBroadcaster* SerialBroadcaster::instance = 0;

SerialBroadcaster::SerialBroadcaster() {
	// TODO Auto-generated constructor stub

}

SerialBroadcaster::~SerialBroadcaster() {
	// TODO Auto-generated destructor stub
}

SerialBroadcaster* SerialBroadcaster::getInstance(){
	if(!instance){
		instance = new SerialBroadcaster();
	}
	return instance;
}

void SerialBroadcaster::validate(){
	int ss = Serial.available();

	if (ss>0) {
		//Serial.print(F("BUF: "));
		//Serial.println(ss);

		// get the new byte:
		char inChar = (char)Serial.read();
		//Serial.println((int)inChar);

		//inputString += inChar;
		// if the incoming character is a newline, set a flag so the main loop can
		// do something about it:
		if (inChar == '\n' || inChar == '\r') {
			//inputString.erase(std::remove_if(
			//		inputString.begin(), inputString.end(), std::isspace),
			//		inputString.end());
			if(inputString.size()>0){
				//inputString.push_back('\r');
				onSerialMessageReceived(inputString);
				Serial.println(inputString.size());
				inputString.clear();
			}
		}
		else
			inputString += inChar;

		if(inputString.size()>16)
			inputString.clear();
	}
	delay(10);
}

void SerialBroadcaster::onSerialMessageReceived(const string msg){
	Serial.print(F("Received: "));
	const char* c = msg.c_str();
	Serial.println(c);
	//msg += "\r";

	//CMD* cmd = new CMDErrorReport();//AT::toCMD(msg);
	//cmd->setSource(SRL);
	//cmd->print();
	//cmd->execute();

	//delete cmd;


	//Serial.print(F("Free RAM = "));
	//Serial.println(freeMemory(), DEC);
	//delete cmd;
	//delete c;
}
