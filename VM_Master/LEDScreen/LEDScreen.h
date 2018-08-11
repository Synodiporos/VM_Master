/*
 * LEDScreen.h
 *
 *  Created on: 6 Αυγ 2018
 *      Author: Synodiporos
 */

#ifndef LEDSCREEN_LEDSCREEN_H_
#define LEDSCREEN_LEDSCREEN_H_

#include <Arduino.h>
#include "../System/SystemConstants.h"

class LEDScreen {
public:
	static LEDScreen* getInstance();
	virtual ~LEDScreen();

	void begin();
	void clear();
	void turnON();
	void turnOFF();
	void brightness(uint8_t br);
	void showMemoryData();
	void write(char* string, int row, int col, uint8_t size);
	void write(char ch, int row, int col, uint8_t size);
	void drawLine(uint8_t x0, uint8_t y0,
			uint8_t x1, uint8_t y1, bool enabled);
	void drawRectangle(uint8_t x0, uint8_t y0,
				uint8_t x1, uint8_t y1, bool enabled);

private:
	static LEDScreen* instance;
	LEDScreen();
	bool onSendAt(char* at);
};

#endif /* LEDSCREEN_LEDSCREEN_H_ */
