
#include "System/SystemConstants.h"
#include "System/NotificationSystem.h"
#include "RFTransceiver/RFTransceiver.h"
#include "LEDScreen/LEDScreen.h"
#include "Memory/MemoryFree.h"
#include "Memory/pgmStrToRAM.h"
#include "WiFi/RequestManager.h"
#include "WiFi/HttpRequest.h"
#include "WiFi/PostSurgeRequest.h"
#include "WiFi/PostBatteryRequest.h"
#include "WiFi/HttpRequestCreator.h"
#include "Controller.h"
#include "SoftwareSerial.h"
#include <Arduino.h>
//#include <avr/pgmspace.h>
using namespace std;

//NotificationSystem* notification = NotificationSystem::getInstance();
//SerialBroadcaster* serialBroad = SerialBroadcaster::getInstance();
//RF24 radio(RF_CE, RF_CSN);
//RFTransceiver* trasnceiver = RFTransceiver::getInstance();
Controller controller;

long mil = millis();
int c = 0;

// the setup routine runs once when you press reset:
void setup() {
	pinMode(LED_WHITE_PIN, OUTPUT);
	pinMode(LED_RED_PIN, OUTPUT);
	pinMode(LED_BLUE_PIN, OUTPUT);

	Serial.begin(SRL_BD);

	//Serial.println(F("MASTER OK"));
	//ledScreen->clear();
	//page->reprint();

	//Initialaze RF
	//trasnceiver->initialize(&radio);
	//trasnceiver->startConnectivityCheck();

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

	//requestManager = RequestManager::getInstance();
	Serial.println(F("START"));


	/*HttpRequest* r1 = new TestGetRequest();
	HttpRequest* r2 = new PostBatteryRequest(415, 200, 0);
	HttpRequest* r3 = new PostSurgeRequest(0, 100000, 10000);
	//String req = HttpRequestCreator::createRequest(r1);
	//uint8_t size = req.length();

	char buffer[88];
	uint8_t size = HttpRequestCreator::createRequest(buffer, r3);
	Serial.println(size);
	Serial.println(buffer);

	size = HttpRequestCreator::createRequest(buffer, r2);
	Serial.println(size);
	Serial.println(buffer);

	size = HttpRequestCreator::createRequest(buffer, r1);
	Serial.println(size);
	Serial.println(buffer);*/

	Serial.print(F("Free RAM = "));
	Serial.println(freeMemory(), DEC);
}

// the loop routine runs over and over again forever:
void loop() {
	controller.validate();
}
