#include "LossnayController.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);

void setup()
{ 
    Serial.begin(74880);
    while (! Serial) {
        delay(1);
    }
    settings.begin();
    wifi.begin();
    webServer.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();

    delay(100);
}
