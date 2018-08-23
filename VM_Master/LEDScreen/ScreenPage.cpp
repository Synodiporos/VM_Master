/*
 * ScreenPage.cpp
 *
 *  Created on: 11 Αυγ 2018
 *      Author: Synodiporos
 */

#include "ScreenPage.h"

ScreenPage::ScreenPage(LEDScreen* screen) :
	screen(screen){
	// TODO Auto-generated constructor stub

}

ScreenPage::~ScreenPage() {
	// TODO Auto-generated destructor stub
}

void ScreenPage::initialize(){

}

void ScreenPage::validate(){

}

bool ScreenPage::setVisible(bool visible){
	if(this->visible!=visible){
		this->visible = visible;
		onPropertyChanged(1);
		return true;
	}
	return false;
}

bool ScreenPage::isVisible(){
	return this->visible;
}

bool ScreenPage::setHV10350(float voltage){
	if(this->hv1!=voltage){
		this->hv1 = voltage;
		//onPropertyChanged(2);
		printHV1();
		return true;
	}
	return false;
}

float ScreenPage::getHV10350(){
	return this->hv1;
}

bool ScreenPage::setHV820(float voltage){
	if(this->hv2!=voltage){
		this->hv2 = voltage;
		//onPropertyChanged(3);
		printHV2();
		return true;
	}
	return false;
}

float ScreenPage::getHV820(){
	return this->hv2;
}

bool ScreenPage::setBatteryLevel(uint8_t level){
	if(this->battery!=level){
		this->battery = level;
		onPropertyChanged(4);
		return true;
	}
	return false;
}

uint8_t ScreenPage::getBatteryLevel(){
	return this->battery;
}

bool ScreenPage::setError(uint8_t error){
	if(this->error!=error){
		this->error = error;
		onPropertyChanged(5);
		return true;
	}
	return false;
}

uint8_t ScreenPage::getError(){
	return this->error;
}

bool ScreenPage::setWarning(uint8_t warning){
	if(this->warning!=warning){
		this->warning = warning;
		onPropertyChanged(6);
		return true;
	}
	return false;
}

uint8_t ScreenPage::getWarning(){
	return this->warning;
}

void ScreenPage::clear(){

}

void ScreenPage::reprint(){
	this->print();
}

void ScreenPage::resetTimer(){

}

void ScreenPage::onPropertyChanged(uint8_t property){
	switch(property){
		case 1:{

			break;
		}
		case 2:{
			printHV1();
			break;
		}
		case 3:{
			printHV2();
			break;
		}
		case 4:{

			break;
		}
		case 5:{

			break;
		}
		case 6:{

			break;
		}
	}
}

void ScreenPage::print(){
	//Serial.println(F("Print Page"));
	//Serial.println((long)screen);
	screen->write("10/",0,0,8);
	screen->write("350",1,0,8);
	screen->write("8/",2,0,8);
	screen->write("20",3,0,8);

	printHV1();
	printHV2();

	//screen->write("BT", 0, 14, 8);
	//screen->write("NC", 2, 14, 8);

	//screen->drawRectangle(32,11,32,13,true);

	//screen->drawLine(0, 15, 96, 15, true);
}

void ScreenPage::printHV1(){
	float hv = getHV10350();
	char f[6] = {0,0,0,0,0,0};
	toStr(hv, f);

	string str;
	if(hv<10){
		str += " ";
		str += f;
	}
	else{
		str += f;
	}
	str += "kV";
	//Serial.println(str.c_str());
	screen->write(str, 0, 3, 16);
}

void ScreenPage::printHV2(){
	float hv = getHV820();
	char f[6] = {0,0,0,0,0,0};
	toStr(hv, f);
	string str;
	if(hv<10){
		str += " ";
		str += f;
	}
	else{
		str += f;
	}
	str += "kV";
	screen->write(str, 2, 3, 16);
}

void ScreenPage::toStr(float value, char str[6]){
	dtostrf(value , 2, 2, str);
}
