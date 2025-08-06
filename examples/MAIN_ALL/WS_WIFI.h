#pragma once

#include "stdio.h"
#include <stdint.h>
#include <WiFi.h>
#include <WebServer.h> 
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "WS_GPIO.h"
#include "WS_Information.h"
#include "WS_Relay.h"
#include "WS_RTC.h"

extern char ipStr[16];
extern bool WIFI_Connection;     

void handleRoot();
void handleGetData();
void handleSwitch(uint8_t ledNumber);

void handleSwitch1();
void handleSwitch2();
void handleSwitch3();
void handleSwitch4();
void handleSwitch5();
void handleSwitch6();
void handleSwitch7();
void handleSwitch8();
void WIFI_Init();
void WIFI_Loop();
void WifiStaTask(void *parameter);

bool parseData(const char* Text, datetime_t* dt, Status_adjustment* Relay, Repetition_event* cycleEvent) ;