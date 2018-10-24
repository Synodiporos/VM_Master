/*
 * Controller.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "Commons/IActionListener.h"
#include "Commons/Action.h"
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
#include "LEDScreen/LEDScreen.h"
#include "LEDScreen/ScreenPage.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
#include "Util/CharUtil.h"
#include "WiFi/GetInfoRequest.h"
using namespace std;

class Controller : public IActionListener{
public:

	Controller();
	virtual ~Controller();

	void activate();
	void deactivate();
	void initialization();

	void actionPerformed(Action action);

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
	bool wifiConnected = false;


	uint8_t helper = 0;
	unsigned long time = millis();
	unsigned long timeToDtRequest = millis();
	unsigned long timeToSurgeRequest = millis();
	//uint8_t c = 0;

	void pushDatetimeRequest();
	void onRFMessageReceived(char* msg);
	void onRFMessageSend(char* msg);
	void onRFSurgeRequestReceived(Surge surge);
	void onRFConnectionStateChanged(bool state);
	//void onACKReceived();
	void onWiFiConnectionStateChanged(bool state);
	void onWifiHttpResponseReceived(
			HttpRequest& request, HttpResponse& response);
	void onHighVoltage1Changed();
	void onHighVoltage2Changed();
	void onHVWarningStateChanged();
	void onBatteryVoltageChagned();
	void onButtonStateChanged();
};

#endif /* CONTROLLER_H_ */
