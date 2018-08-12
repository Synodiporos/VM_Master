
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
	RF24 radio(RF_CE, RF_CSN);
	trasnceiver->initialize(&radio);

	//Controller
	controller.activate();
	controller.initialization();

	CMDStartUp* startUp = new CMDStartUp();
	startUp->execute();

	//Serial.print(F("Free RAM = ")); //F function does the same and is now a built in library, in IDE > 1.0.0
	//Serial.println(freeMemory(), DEC);  // print how much RAM is available.
	// print how much RAM is available.
}

// the loop routine runs over and over again forever:
void loop() {
	long interval = millis()-mil;

	/*if(interval>=2000 && c<=12){
		switch(c){
			case 0:{
				ledScreen->turnOFF();
				break;
			}
			case 1:{
				ledScreen->turnON();
				break;
			}
			case 2:{
				ledScreen->showMemoryData();
				break;
			}
			case 3:{
				ledScreen->clear();
				break;
			}
			case 4:{
				char str[] = "Test1!";
				ledScreen->write(str, 0, 0, 8);
				break;
			}
			case 5:{
				char str[] = "Test2!";
				ledScreen->write(str, 0, 0, 16);
				break;
			}
			case 6:{
				ledScreen->write('A', 2, 2, 7);
				break;
			}
			case 7:{
				ledScreen->write('B', 0, 5, 16);
				break;
			}
			case 8:{
				ledScreen->drawLine(1, 15, 94, 15, true);
				break;
			}
			case 9:{
				ledScreen->drawRectangle(0, 0, 95, 31, true);
				break;
			}
			case 10:{
				ledScreen->brightness(1);
				break;
			}
			case 11:{
				ledScreen->brightness(6);
				break;
			}
			case 12:{
				ledScreen->brightness(11);
				//c = -1;
				break;
			}
		}
		c++;
		mil = millis();
	}

	if(interval>=2000 && c>12){
		char buffer [13 + 1];
		sprintf (buffer, "V=%dkV", c);
		ledScreen->write(buffer, 2, 0, 16);
		if(c>1000)
			c=0;
		else
			c++;
		delay(50);
	}*/

	notification->validate();
	serialBroad->validate();
	trasnceiver->validate();
	executor->validate();
}
