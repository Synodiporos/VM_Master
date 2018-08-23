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

protected:
	NotificationSystem* notification = NotificationSystem::getInstance();
	RFTransceiver* transceiver = RFTransceiver::getInstance();
	LEDScreen* screen = LEDScreen::getInstance();
	ScreenPage* page = new ScreenPage(screen);

	void onMessageReceived(char* msg);
	void onMessageSend(char* msg);
	void onConnectionStateChanged(bool state);
};

#endif /* CONTROLLER_H_ */
