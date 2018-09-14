/*
 * LEDScreen.cpp
 *
 *  Created on: 6 Αυγ 2018
 *      Author: Synodiporos
 */

#include "LEDScreen.h"

LEDScreen* LEDScreen::instance = nullptr;

LEDScreen::LEDScreen() {
	this->begin();
}

LEDScreen::~LEDScreen() {
	// TODO Auto-generated destructor stub
}

LEDScreen* LEDScreen::getInstance(){
	if(!instance)
		instance = new LEDScreen();
	return instance;
}

void LEDScreen::begin(){
	Serial.begin(SRL3_BD);
}

void LEDScreen::clear(){
	char at[] = "ATd0=()";
	onSendAt(at);
}

void LEDScreen::turnON(){
	char at[] = "ATf1=()";
	onSendAt(at);
}

void LEDScreen::turnOFF(){
	char at[] = "ATf0=()";
	onSendAt(at);
}

void LEDScreen::brightness(uint8_t br){
	char buffer [10];
	int b = br;
	sprintf (buffer, "ATf2=(%d)", b);
	onSendAt(buffer);
}

void LEDScreen::showMemoryData(){
	char at[] = "ATd1=()";
	onSendAt(at);
}

void LEDScreen::write(std::string string, int row, int col, uint8_t size){
	char buffer [13 + string.size()];
	int n;
	if(size<16)
		n = sprintf (buffer, "AT81=(%d,%d,%s)", row, col, string.c_str());
	else
		n = sprintf (buffer, "AT83=(%d,%d,%s)", row, col, string.c_str());
	onSendAt(buffer);
}

void LEDScreen::write(char ch, int row, int col, uint8_t size){
	char buffer [13 + 1];
	int n;
	if(size<16)
		n = sprintf (buffer, "AT80=(%d,%d,%c)", row, col, ch);
	else
		n = sprintf (buffer, "AT82=(%d,%d,%c)", row, col, ch);
	onSendAt(buffer);
}

void LEDScreen::drawLine(uint8_t x0, uint8_t y0,
			uint8_t x1, uint8_t y1, bool enabled){
	char buffer [21];
	uint8_t in = 0;
	if(enabled)
		in = 1;
	sprintf (buffer, "AT90=(%d,%d,%d,%d,%d)", x0, y0, x1, y1, in);
	onSendAt(buffer);
}

void LEDScreen::drawRectangle(uint8_t x0, uint8_t y0,
			uint8_t x1, uint8_t y1, bool enabled){
	char buffer [21];
	uint8_t in = 0;
	if(enabled)
		in = 1;
	sprintf (buffer, "AT91=(%d,%d,%d,%d,%d)", x0, y0, x1, y1, in);
	onSendAt(buffer);
}

bool LEDScreen::onSendAt(char* at){
	uint8_t res = Serial.print(at);

	unsigned long time = millis();
	bool timeout = false;
	while(Serial.read()!='E' && !timeout){
		timeout = millis()-time >= SC_TIMEOUT;
	}
	delay(1);

	if(timeout)
		onTimeout();
	//Serial.println();
	//delay(10);
	//delete at;
	return res>0;
}

void LEDScreen::onTimeout(){
	//Serial.println(F("Time out"));
}
