/*
 * NotificationSystem.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_NOTIFICATIONSYSTEM_H_
#define SYSTEM_NOTIFICATIONSYSTEM_H_
#include "SystemConstants.h"
#include <Arduino.h>

class NotificationSystem {
public:
	static NotificationSystem* getInstance();
	virtual ~NotificationSystem();
	void initialize();
	void validate();

private:
	static NotificationSystem* instance;
	byte state = 00000000;
	#define HV_WARNING 128
	#define BATTERY 64
	#define ERROR 32
	#define CONNECTION_LOST 16
	#define TRANSFER 8
	#define ACTIVE	4


	NotificationSystem();
	void onStateChanged(byte change);
};

#endif /* SYSTEM_NOTIFICATIONSYSTEM_H_ */
