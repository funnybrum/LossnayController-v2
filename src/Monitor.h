#pragma once

#include "LossnayController.h"

class Monitor {
    public:
        Monitor();
        void begin();
        void loop();

        int8_t getBypassIndicator();
        int8_t getMalfunctionIndicator();
        int8_t getOperatingIndicator();
        int16_t getAnalog();

    private:
        int8_t _bypass = -1;
        int8_t _malfunction = -1;
        int8_t _operating = -1;
        int16_t _analog = -1;
};
