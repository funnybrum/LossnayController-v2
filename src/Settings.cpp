#include "LossnayController.h"
#include <EEPROM.h>

void Settings::begin() {
    EEPROM.begin(DATA_SIZE);
    for (unsigned int i = 0; i < DATA_SIZE; i++) {
        *(((uint8_t*)&this->data) + i) = EEPROM.read(i);
    }
    EEPROM.end();

    // TODO: There are two values used for checksum validation currently. Once all
    // devices are migrated - switch to proper checsum algorithm.
    if (data.checksum == TEMP_CHECKSUM_VAL || data.checksum == TEMP_CHECKSUM_VAL + 1) {
        logger.log("Settings loaded successfully");
    } else {
        memset(&this->data, 0, DATA_SIZE);
        logger.log("Failed to load settings");
    }
}

void Settings::loop() {
}

void Settings::erase() {
    logger.log("Erasing EEPROM");
    memset(&this->data, 0, DATA_SIZE);
    this->data.checksum = 0;
    this->writeToEEPROM();
}

void Settings::save() {
    logger.log("Writing state to EEPROM");
    this->data.checksum = TEMP_CHECKSUM_VAL;
    this->writeToEEPROM();
}

void Settings::writeToEEPROM() {
    EEPROM.begin(DATA_SIZE);
    for (unsigned int i = 0; i < DATA_SIZE; i++) {
        EEPROM.write(i, *(((uint8_t*)&this->data) + i));
    }
    EEPROM.end();
}

SettingsData* Settings::get() {
    return &this->data;
}

Settings settings = Settings();
