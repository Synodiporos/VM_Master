/*
 * ScreenPage.h
 *
 *  Created on: 11 Αυγ 2018
 *      Author: Synodiporos
 */

#ifndef LEDSCREEN_SCREENPAGE_H_
#define LEDSCREEN_SCREENPAGE_H_

#include "../LEDScreen/LEDScreen.h"
#include <Arduino.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class ScreenPage {
public:
	ScreenPage(LEDScreen* screen);
	virtual ~ScreenPage();
	void initialize();
	void validate();

	bool setVisible(bool visible);
	bool isVisible();
	bool setHV10350(float voltage);
	float getHV10350();
	bool setHV820(float voltage);
	float getHV820();
	bool setBatteryLevel(uint8_t level);
	uint8_t getBatteryLevel();
	bool setError(uint8_t error);
	uint8_t getError();
	bool setWarning(uint8_t warning);
	uint8_t getWarning();

	void clear();
	void reprint();

private:
	LEDScreen* screen = nullptr;
	bool visible = true;
	float hv1 = 0;
	float hv2 = 0;
	uint8_t battery = 0;
	uint8_t error = 0;
	uint8_t warning = 0;

	void resetTimer();
	void onPropertyChanged(uint8_t property);
	void print();
	void toStr(float value, char str[6]);

	void printHV1();
	void printHV2();

};

#endif /* LEDSCREEN_SCREENPAGE_H_ */
