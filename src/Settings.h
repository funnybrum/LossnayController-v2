#pragma once

#include "SettingsBase.h"
#include "WiFi.h"
#include "BME280.h"
#include "InfluxDBCollector.h"

struct SettingsData {
    NetworkSettings network;
    BME280Settings returnAir;
    BME280Settings supplyAir;
    InfluxDBCollectorSettings influxDB;
};

struct Empty {};

class Settings: public SettingsBase<SettingsData, Empty> {
    public:
        Settings();
        SettingsData* getSettings();

    protected:
        void initializeSettings();
        Empty* getRTCSettings();

    private:
        SettingsData settingsData;
};
