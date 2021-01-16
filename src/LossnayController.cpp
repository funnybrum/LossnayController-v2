#include "LossnayController.h"

void setup()
{
    logger.begin();

    settings.begin();

    ScanAndConnect();

    webServer.begin();
    systemCheck.begin();
    lossnay.begin();
}

void loop() {
    webServer.loop();
    settings.loop();
    systemCheck.loop();
    logger.loop();
    lossnay.loop();
    delay(100);
}
