#include "LossnayController.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      NULL,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return returnAirSensor.getHumidity() > 0;
}

void DataCollector::collectData() {
    append("ra_temperature", returnAirSensor.getTemperature(), 2);
    append("ra_humidity", returnAirSensor.getHumidity(), 1);
    append("ra_pressure", returnAirSensor.getPressure(), 0);
    append("ra_abs_humidity", returnAirSensor.getAbsoluteHimidity(), 2);
    append("sa_temperature", supplyAirSensor.getTemperature(), 2);
    append("sa_humidity", supplyAirSensor.getHumidity(), 1);
    append("sa_pressure", supplyAirSensor.getPressure(), 0);
    append("sa_abs_humidity", supplyAirSensor.getAbsoluteHimidity(), 2);

    append("bypass", fanController.getMode() == BYPASS, 0);
    append("on", fanController.isPowered(), 0);
    append("speed", fanController.getSpeed(), 0);
    append("i_bypass", monitor.getBypassIndicator(), 0);
    append("i_malfunction", monitor.getMalfunctionIndicator(), 0);
    append("i_operating", monitor.getOperatingIndicator(), 0);
}

bool DataCollector::shouldPush() {
    return false;
}   

void DataCollector::beforePush() {
    append("rssi", WiFi.RSSI(), 0);
}

void DataCollector::afterPush() {
}