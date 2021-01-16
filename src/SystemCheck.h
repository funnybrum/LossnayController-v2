#ifndef _SYSTEM_CHECK_H_
#define _SYSTEM_CHECK_H_

#include "LossnayController.h"

class SystemCheck {
    public:
        void begin();
        void loop();
        void registerWebCall();
    private:
        unsigned long lastWebCall;
        unsigned long lastWiFiConnectedState;
        bool hasTimeoutOccur(unsigned long timer, unsigned  int timeoutSeconds);
};

extern SystemCheck systemCheck;

#endif
