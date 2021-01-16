#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "LossnayController.h"

struct SettingsData {
    uint8_t checksum;
    char hostname[64];
};

#define DATA_SIZE sizeof(SettingsData)
// Temporary replacement for the calculated checksum to allow lossless migration.
#define TEMP_CHECKSUM_VAL 101

class Settings {
    public:
        void begin();
        void loop();
        void save();
        void erase();
        /**
         * Get the stored settings. If there was no saved settings the result
         * will be initialized with zeroes.
         */
        SettingsData* get();
    private:
        SettingsData data;
        void writeToEEPROM();
};

extern Settings settings;

#endif
