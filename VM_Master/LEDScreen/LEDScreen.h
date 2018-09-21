/*
 * LEDScreen.h
 *
 *  Created on: 6 Αυγ 2018
 *      Author: Synodiporos
 */

#ifndef LEDSCREEN_LEDSCREEN_H_
#define LEDSCREEN_LEDSCREEN_H_

#include <Arduino.h>
#include <string>
#include "../System/SystemConstants.h"

#define AT_CLEAR "ATd0=()"
#define AT_TURNON "ATf1=()"
#define AT_TURNOFF "ATf0=()"
#define AT_BRIGHT "ATf2=(%d)"
#define AT_WRITE_STRING "AT8%d=(%d,%d,%s)"
#define AT_WRITE_CHAR "AT8%d=(%d,%d,%c)"
#define AT_DRAW_LINE "AT90=(%d,%d,%d,%d,%d)"
#define AT_DRAW_RECTANGLE "AT91=(%d,%d,%d,%d,%d)"


class LEDScreen {
public:
	static LEDScreen* getInstance();
	virtual ~LEDScreen();

	void begin();
	void clear();
	void turnON();
	void turnOFF();
	void brightness(uint8_t br);
	void write(std::string string, int row, int col, uint8_t size);
	void write(char ch, int row, int col, uint8_t size);
	void drawLine(uint8_t x0, uint8_t y0,
			uint8_t x1, uint8_t y1, bool enabled);
	void drawRectangle(uint8_t x0, uint8_t y0,
				uint8_t x1, uint8_t y1, bool enabled);

private:
	static LEDScreen* instance;
	LEDScreen();
	bool onSendAt(char* at);
	void onTimeout();
};

#endif /* LEDSCREEN_LEDSCREEN_H_ */
