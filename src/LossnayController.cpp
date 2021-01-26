#include "LossnayController.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
DataCollector dataCollector = DataCollector();
FanController fanController = FanController();
BME280 returnAirSensor = BME280(&settings.getSettings()->returnAir, 0x77, "ra", "Supply Air Sensor");
BME280 supplyAirSensor = BME280(&settings.getSettings()->supplyAir, 0x76, "sa", "Return Air Sensor");

void setup()
{ 
    Serial.begin(74880);
    while (! Serial) {
        delay(1);
    }
    settings.begin();
    wifi.begin();
    webServer.begin();

    fanController.begin();
    returnAirSensor.begin();
    supplyAirSensor.begin();

    dataCollector.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();

    fanController.loop();
    returnAirSensor.loop();
    supplyAirSensor.loop();
    dataCollector.loop();

    delay(100);
}
