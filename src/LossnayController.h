#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>

#include "user_interface.h"

#include "esp8266-base.h"

#include "DataCollector.h"
#include "BME280.h"
#include "FanController.h"
#include "Monitor.h"

#define HTTP_PORT 80
#define HOSTNAME "ventilator"

// GPIO pins
#define ON_OFF_PIN         D3
#define FAN_SPEED_1_PIN    D8
#define FAN_SPEED_2_PIN    D7
#define FAN_SPEED_3_PIN    D6
#define FAN_SPEED_4_PIN    D5
#define BYPASS_PIN         D4

extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;
extern DataCollector dataCollector;
extern FanController fanController;
extern BME280 returnAirSensor;
extern BME280 supplyAirSensor;
extern Monitor monitor;
