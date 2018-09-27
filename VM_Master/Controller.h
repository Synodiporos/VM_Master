/*
 * Controller.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Math/MathUtil.h"
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "Commons/IPropertyListener.h"
#include "Commons/IStateListener.h"
#include "Commons/State.h"
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "Button/Button.h"
#include "RFTransceiver/RFTransceiver.h"
#include "WiFi/RequestManager.h"
#include "WiFi/HttpRequest.h"
#include "WiFi/PostSurgeRequest.h"
#include "WiFi/PostBatteryRequest.h"
#include "WiFi/TestGetRequest.h"
#include "LEDScreen/LEDScreen.h"
#include "LEDScreen/ScreenPage.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
#include "Util/CharUtil.h"
#include <string>
#include <SPI.h>
#include <RF24.h>
using namespace std;


class Controller : public IPropertyListener, IActionListener,
	IStateListener{
public:

	Controller();
	virtual ~Controller();

	void activate();
	void deactivate();
	void initialization();
	void setRadioInstance(RF24* radio);

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);
	void actionPerformed(Action action);
	void stateChanged(State state);

	void validate();

protected:
	Button* button = new Button(BUTTON_PIN);
	//NotificationSystem* notification = NotificationSystem::getInstance();
	RFTransceiver* transceiver = RFTransceiver::getInstance();
	RequestManager* requestManager = RequestManager::getInstance();
	LEDScreen* screen = LEDScreen::getInstance();
	//ScreenPage* page = new ScreenPage(screen);


	unsigned long HV1 = 0;
	unsigned long HV2 = 0;
	float batteryVoltage = 0;

	uint8_t helper = 0;
	unsigned long time = millis();
	uint8_t c = 0;

	void onMessageReceived(char* msg);
	void onMessageSend(char* msg);
	void onRFConnectionStateChanged(bool state);
	void onACKReceived();
	void onWiFiConnectionStateChanged(bool state);
	void onHighVoltage1Changed();
	void onHighVoltage2Changed();
	void onBatteryVoltageChagned();
	void onButtonStateChanged();
};

#endif /* CONTROLLER_H_ */
