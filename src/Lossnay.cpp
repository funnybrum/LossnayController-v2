#include "LossnayController.h"

void Lossnay::begin() {
    pinMode(ON_OFF_PIN, OUTPUT);
    pinMode(FAN_SPEED_1, OUTPUT);
    pinMode(FAN_SPEED_2, OUTPUT);
    pinMode(FAN_SPEED_3, OUTPUT);
    pinMode(FAN_SPEED_4, OUTPUT);

    update = true;
    loop();
}

void Lossnay::loop() {
    if (update) {
        logger.log("Setting state to %d and speed to %d", working, speed);
        if (working) {
            digitalWrite(ON_OFF_PIN, HIGH);
        } else {
            digitalWrite(ON_OFF_PIN, LOW);
        }

        digitalWrite(FAN_SPEED_1, speed==1);
        digitalWrite(FAN_SPEED_2, speed==2);
        digitalWrite(FAN_SPEED_3, speed==3);
        digitalWrite(FAN_SPEED_4, speed==4);

        update = false;
    }
}

void Lossnay::fan_speed(uint8_t speed) {
    if (this->speed == speed) {
        return;
    }

    this->speed = speed;
    update = true;
}

void Lossnay::turn_on() {
    if (working) {
        return;
    }

    update = true;
    working = true;
}

void Lossnay::turn_off() {
    if (!working) {
        return;
    }

    update = true;
    working = false;
}

Lossnay lossnay = Lossnay();
