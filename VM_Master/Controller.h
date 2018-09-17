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
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "RFTransceiver/RFTransceiver.h"
#include "WiFi/RequestManager.h"
#include "WiFi/HttpRequest.h"
#include "WiFi/PostSurgeRequest.h"
#include "WiFi/TestGetRequest.h"
#include "CMD/AT.h"
#include "LEDScreen/LEDScreen.h"
#include "LEDScreen/ScreenPage.h"
#include <vector>
#include <string>
using namespace std;

class Controller : public IPropertyListener, IActionListener{
public:
	Controller();
	virtual ~Controller();

	void activate();
	void deactivate();
	void initialization();
	void setNotificationSystem(NotificationSystem* ns);
	void setLoggerSystem();
	void setRFDevice();

	void propertyChanged(
				void* source,
				unsigned short int propertyId,
				const void* oldPropery);
	void actionPerformed(Action action);

	void validate();

protected:
	//NotificationSystem* notification = NotificationSystem::getInstance();
	RFTransceiver* transceiver = RFTransceiver::getInstance();
	RequestManager* requestManager = RequestManager::getInstance();

	LEDScreen* screen = LEDScreen::getInstance();
	ScreenPage* page = new ScreenPage(screen);

	unsigned long HV1 = 0;
	unsigned long HV2 = 0;
	float batteryVoltage = 0;

	uint8_t helper = 0;
	unsigned long time = millis();
	uint8_t c = 0;

	void onMessageReceived(char* msg);
	void onMessageSend(char* msg);
	void onRFConnectionStateChanged(bool state);
	void onWiFiConnectionStateChanged(bool state);
};

#endif /* CONTROLLER_H_ */
