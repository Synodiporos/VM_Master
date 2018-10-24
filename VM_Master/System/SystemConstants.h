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
#define SRL3_BD 9600
//Serial
#define SRL_BD 115200
//RF CONFIG
#define RF_READ_PIPE (byte) 00002
#define RF_WRITE_PIPE (byte) 00001
#define RF_CC_PERIOD 8000
#define RF_CC_INTERVALS 500
#define RF_PAYLOAD_SIZE 24
#define RF_PALEVEL RF24_PA_LOW
#define RF_DATARATE RF24_250KBPS//RF24_1MBPS//RF24_250KBPS
//WIFI
#define WIFI_CHECK_INTERVAL 30000
#define WIFI_AUTOCONNECT true
#define WIFI_SSID "RaycapWiFi_Drama" //"Syn-2" //"SynNet" //"RaycapWiFi_Drama"
#define WIFI_PASS "r@yL@N!!" //"6987881596" //"Syn123NET789" //"r@yL@N!!"
#define WIFI_SERVER "192.168.11.5" //"synet.sytes.net" //"192.168.11.5"
#define WIFI_SURGEROOM_URI "/rnd/util" //"/surges"
#define WIFI_TEST_URI "/test.php" //"/surges/test5.php" //"/get.php"
#define WIFI_DATETIME_URI "/dt.php"
#define WIFI_INFO_URI "/dt.php"
#define WIFI_SURGE_URI "/srg.php"
#define WIFI_BATTERY_URI "/btr.php"
//
#define REQUEST_URL_PARAMS_LENGHT 48
#define REQUEST_URL_LENGHT9 56
#define REQUEST_HEADER_LENGHT 96
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
//System Parameters
#define DATETIME_REQUEST_INTERVAL 21600000 //21600000  //3600000 1H

#endif /* SYSTEM_SYSTEMCONSTANTS_H_ */
