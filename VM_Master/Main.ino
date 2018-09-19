
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
#include "WiFi/TestGetRequest.h"
#include "Controller.h"
#include "SoftwareSerial.h"
#include <SPI.h>
#include <RF24.h>
#include <string>
#include <Arduino.h>
#include <avr/pgmspace.h>
using namespace std;



//NotificationSystem* notification = NotificationSystem::getInstance();
//SerialBroadcaster* serialBroad = SerialBroadcaster::getInstance();
RF24 radio(RF_CE, RF_CSN);
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
	controller.setRadioInstance(&radio);
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

	Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);
	Serial.println(F("START"));


	Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	Serial.println(freeMemory(), DEC);

}

// the loop routine runs over and over again forever:
void loop() {
	long interval = millis()-mil;

	if(interval>= 2000 ){
		//Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
		//Serial.println(freeMemory(), DEC);
		mil = millis();
	}


	/*if(c==0){
		esp->println(F("AT+CWMODE=3"));
		Serial.print(F("SEVD AT"));
		c=1;
	}
	delay(50);

	if (esp->available()){
		while (esp->available() > 0 ){
			//Serial.println(F("-"));
			String response = esp->readStringUntil('\n');
			response.trim();
			if(response.length()>0){
				std::string str(response.c_str());

				Serial.print(F("Received: "));
				Serial.println(str.c_str());

				if(str.compare("OK")==0){
					c=0;
				}
				//onEspMessageReceived(str);
			}
			//Serial.println(F("+"));
		}
	}*/

	//trasnceiver->validate();
	//notification->validate();
	//serialBroad->validate();
	//executor->validate();
	controller.validate();
}
