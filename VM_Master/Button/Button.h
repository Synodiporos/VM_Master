/*
 * Button.h
 *
 *  Created on: 24 Ξ�Ξ±Ο� 2018
 *      Author: Synodiporos
 */
#include <Arduino.h>
#include "../Commons/IActionListener.h"
#include <stdint.h>

#ifndef BUTTON_H_
#define BUTTON_H_

enum class ButtonState { PRESSED, RELEASED, CLICKED, HOLDED };

class Button{
public:
	static unsigned short int filterInterval;
	static unsigned short int holdStateInterval;

	Button(uint8_t pinNumber);
	virtual ~Button();
	uint8_t getPinNumber();
	ButtonState getButtonState();
	unsigned long getLastEventTime();
	unsigned long getIntervalFromLastEvent();
	IActionListener* getActionListener();
	void setActionListener(IActionListener* l);
	void validate();

private:
	uint8_t pinNumber = -1;
	unsigned long lastEventTime = 0;
	ButtonState buttonState = ButtonState::RELEASED;
	IActionListener* listener = 0;

	void setButtonState(const ButtonState state);
	void press();
	void release();
	void click();
	void hold();
	void updateLastTimeEvent();
	void notifyButtonStateChanged();
};

#endif /* BUTTON_H_ */
