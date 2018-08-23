
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "System/SerialBroadcaster.h"
#include "RFTransceiver/RFTransceiver.h"
#include "LEDScreen/LEDScreen.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
#include "CMD/CMD.h"
#include "CMD/CMDStartUp.h"
#include "Controller.h"
#include <SPI.h>
#include <RF24.h>
#include <string>
#include <Arduino.h>
using namespace std;

NotificationSystem* notification = NotificationSystem::getInstance();
SerialBroadcaster* serialBroad = SerialBroadcaster::getInstance();
RFTransceiver* trasnceiver = RFTransceiver::getInstance();
CMDExecutor* executor = CMDExecutor::getInstance();
LEDScreen* ledScreen = LEDScreen::getInstance();
ScreenPage* page = new ScreenPage(ledScreen);
Controller controller;
RF24 radio(RF_CE, RF_CSN);

long mil = millis();
int c = 0;

// the setup routine runs once when you press reset:
void setup() {
	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	pinMode(LED_BLUE_PIN, OUTPUT);

	Serial.begin(SRL_BD);

	//Serial.println(F("MASTER OK"));
	ledScreen->clear();
	//page->reprint();

	//Initialaze RF
	trasnceiver->initialize(&radio);
	trasnceiver->startConnectivityCheck();

	//Controller
	controller.activate();
	controller.initialization();

	digitalWrite(LED_WHITE_PIN, HIGH);
	digitalWrite(LED_RED_PIN, HIGH);
	digitalWrite(LED_BLUE_PIN, HIGH);
	delay(250);
	digitalWrite(LED_WHITE_PIN, LOW);
	digitalWrite(LED_RED_PIN, LOW);
	digitalWrite(LED_BLUE_PIN, LOW);

	//controller.activate();

	//Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	//Serial.println(freeMemory(), DEC);  // print how much RAM is available.
	// print how much RAM is available.
}

// the loop routine runs over and over again forever:
void loop() {
	long interval = millis()-mil;

	if(interval>=2000 ){
		//Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
		//Serial.println(freeMemory(), DEC);
		mil = millis();
	}

	trasnceiver->validate();
	notification->validate();
	//serialBroad->validate();
	//executor->validate();
}
