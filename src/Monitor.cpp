#include "LossnayController.h"

int16_t ANALOG_MAP[] = {1024, 965, 865, 776, 710, 648, 600, 556};
int16_t SPREAD = 10;

Monitor::Monitor() {
}

void Monitor::begin() {
}

void Monitor::loop() {
    _analog = analogRead(A0);

    int8_t pos = -1;
    for (int8_t i = 0; i < 8; i++) {
        if (abs(ANALOG_MAP[i] - _analog) < SPREAD) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        _bypass = -1;
        _malfunction = -1;
        _operating = -1;
        return;
    }

    _bypass      = (pos >> 2) & 1;
    _malfunction = (pos >> 1) & 1;
    _operating   = pos & 1;
}

int8_t Monitor::getBypassIndicator() {
    return _bypass;
}

int8_t Monitor::getMalfunctionIndicator() {
    return _malfunction;
}

int8_t Monitor::getOperatingIndicator() {
    return _operating;
}

int16_t Monitor::getAnalog() {
    return _analog;
}
