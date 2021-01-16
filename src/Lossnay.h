#ifndef _LOSSNAY_H_
#define _LOSSNAY_H_

#include "LossnayController.h"

class Lossnay {
    public:
        void begin();
        void loop();
        void fan_speed(uint8_t speed);
        void turn_on();
        void turn_off();
    private:
        bool update = false;
        uint8_t speed = 0;
        bool working = false;
};

extern Lossnay lossnay;

#endif
