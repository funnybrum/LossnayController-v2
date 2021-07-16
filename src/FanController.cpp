#include "LossnayController.h"

FanController::FanController() {
    pinMode(ON_OFF_PIN, OUTPUT);
    pinMode(FAN_SPEED_1_PIN, OUTPUT);
    pinMode(FAN_SPEED_2_PIN, OUTPUT);
    pinMode(FAN_SPEED_3_PIN, OUTPUT);
    pinMode(FAN_SPEED_4_PIN, OUTPUT);
    pinMode(BYPASS_PIN, OUTPUT);

    _changes = true;
    loop();
}

void FanController::begin() {
}

void FanController::loop() {
    if (_changes) {
        digitalWrite(ON_OFF_PIN, _powered?LOW:HIGH);
        digitalWrite(FAN_SPEED_1_PIN, (_speed==1)?HIGH:LOW);
        digitalWrite(FAN_SPEED_2_PIN, (_speed==2)?HIGH:LOW);
        digitalWrite(FAN_SPEED_3_PIN, (_speed==3)?HIGH:LOW);
        digitalWrite(FAN_SPEED_4_PIN, (_speed==4)?HIGH:LOW);
        digitalWrite(BYPASS_PIN, (_mode==BYPASS)?LOW:HIGH);
        _changes = false;

        logger.log("Setting mode to %s/%d/%s",
            _powered?"on":"off",
            _speed,
            (_mode==BYPASS)?"bypass":"lossnay");
    }
}

void FanController::on() {
    if (_powered == false) {
        _powered = true;
        _changes = true;
    }
}

void FanController::off() {
    if (_powered == true) {
        _powered = false;
        _changes = true;
    }
}

void FanController::setSpeed(uint8_t speed) {
    if (_speed != speed) {
        _speed = speed;
        _changes = true;
    }
}

void FanController::setMode(Mode mode) {
    if (_mode != mode) {
        _mode = mode;
        _changes = true;
    }
}

bool FanController::isPowered() {
    return _powered;
}

uint8_t FanController::getSpeed() {
    return _speed;
}

Mode FanController::getMode() {
    return _mode;
}