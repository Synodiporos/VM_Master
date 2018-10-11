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
#include "System/UnixTime.h"
#include "System/PersistBuffer.h"
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
using namespace std;


class Controller : public IPropertyListener, IActionListener,
	IStateListener{
public:

	Controller();
	virtual ~Controller();

	void activate();
	void deactivate();
	void initialization();

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);
	void actionPerformed(Action action);
	void stateChanged(State state);

	void validate();

protected:
	Button* button = new Button(BUTTON_PIN);
	NotificationSystem* notification = NotificationSystem::getInstance();
	RFTransceiver* transceiver = RFTransceiver::getInstance();
	PersistBuffer* requestBuffer = PersistBuffer::getInstance();
	RequestManager* requestManager = RequestManager::getInstance();
	LEDScreen* screen = LEDScreen::getInstance();
	ScreenPage* page = new ScreenPage(screen);


	float HV1 = 0;
	float HV2 = 0;
	bool HVWARNING = false;
	float batteryVoltage = 0;


	uint8_t helper = 0;
	unsigned long time = millis();
	uint8_t c = 0;

	void onRFMessageReceived(char* msg);
	void onRFMessageSend(char* msg);
	void onRFMessageSendError(char* msg);
	void onRFSurgeRequestReceived(Surge surge);
	void onRFConnectionStateChanged(bool state);
	void onACKReceived();
	void onWiFiConnectionStateChanged(bool state);
	void onHighVoltage1Changed();
	void onHighVoltage2Changed();
	void onHVWarningStateChanged();
	void onBatteryVoltageChagned();
	void onButtonStateChanged();
};

#endif /* CONTROLLER_H_ */
