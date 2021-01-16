#ifndef _POWER_MONITOR_H_
#define _POWER_MONITOR_H_

#define HTTP_PORT 80
#define HOSTNAME "ventilator"

#define LOG_SIZE 256

// GPIO PINS
#define ON_OFF_PIN  D0
#define FAN_SPEED_1 D1
#define FAN_SPEED_2 D2
#define FAN_SPEED_3 D6
#define FAN_SPEED_4 D7

#define LOG_TO_SERIAL

#define MIN_TO_MILLIS(mins) (mins * 60L * 1000L)

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "Settings.h"
#include "SystemCheck.h"
#include "WebServer.h"
#include "WiFi.h"
#include "Logger.h"
#include "Lossnay.h"

#endif
