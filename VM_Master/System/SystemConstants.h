/*
 * SystemConstants.h
 *
 *  Created on: Jul 2, 2018
 *      Author: sgeorgiadis
 */

#ifndef SYSTEM_SYSTEMCONSTANTS_H_
#define SYSTEM_SYSTEMCONSTANTS_H_

//PIN NUMBER CONGIG
#define LED_RED_PIN 7
#define LED_BLUE_PIN 6
#define LED_WHITE_PIN 5
#define BUTTON_PIN 4
#define RF_CE 9
#define RF_CSN 10
#define RF_IRQ 8
#define RX3_PIN 2
#define TX3_PIN 3

//Serial 3
#define SRL3_BD 115200
//Serial
#define SRL_BD 115200

//RF CONFIG
#define RF_READ_PIPE (byte) 00002
#define RF_WRITE_PIPE (byte) 00001
#define RF_CC_PERIOD 10000
#define RF_PAYLOAD_SIZE 16
//SCREEN CONFIG
#define SC_TIMEOUT 40
#define SC_TURNOFF_INT 60000
//AT COMMANDS
#define CMD_HV1 "HV1"
#define CMD_SR1 "SR1"
#define CMD_HV2 "HV2"
#define CMD_SR2 "SR2"
#define CMD_BAT "BAT"
#define CMD_ACK "ACK"
#define CMD_ACR "ACR"
//LED NOTIFICATION MODES
//ACTIVE
#define LED_M1 new LEDTone(3, 40,	\
		new LEDTone(255, 20, \
		new LEDTone(0, 2940)))
//CONNECTION_LOST
#define LED_M3 new LEDTone(255, 50, \
		new LEDTone(0, 950))
//TRANSFER
#define LED_M4_ITER 1;
#define LED_M4 new LEDTone(255, 25, \
		new LEDTone(0, 75, \
		new LEDTone(255, 25, \
		new LEDTone(0, 2775 \
))))
//HV_WARNING
#define LED_M5 new LEDTone(255, 40, \
		new LEDTone(0, 60, \
		new LEDTone(255, 40, \
		new LEDTone(0, 60, \
		new LEDTone(255, 40, \
		new LEDTone(0, 60, \
		new LEDTone(255, 40, \
		new LEDTone(0, 60, \
		new LEDTone(255, 40, \
		new LEDTone(0, 60, \
		new LEDTone(255, 40, \
		new LEDTone(0, 460 \
))))))))))))
//BATTERY
#define LED_M6 new LEDTone(255, 25, \
		new LEDTone(0, 2985 \
))
//ERROR
#define LED_M7 new LEDTone(255, 750,\
		new LEDTone(0, 750))


#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */