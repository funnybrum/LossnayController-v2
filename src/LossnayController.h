#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "esp8266-base.h"

#define HTTP_PORT 80
#define HOSTNAME "ventilator"

// GPIO PINS
#define ON_OFF_PIN  D0
#define FAN_SPEED_1 D1
#define FAN_SPEED_2 D2
#define FAN_SPEED_3 D6
#define FAN_SPEED_4 D7


extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;
extern SystemCheck systemCheck;
