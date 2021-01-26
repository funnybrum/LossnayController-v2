#pragma once

#include "LossnayController.h"

enum Mode {
    LOSSNAY,
    BYPASS
};

class FanController {
    public:
        FanController();
        void begin();
        void loop();

        void on();
        void off();
        void setSpeed(uint8_t speed);
        void setMode(Mode mode);

        bool isPowered();
        uint8_t getSpeed();
        Mode getMode();

    private:
        uint8_t _speed = 1;
        bool _powered = true;
        bool _changes = false;
        bool _bypassed = false;
        Mode _mode = LOSSNAY;
};
