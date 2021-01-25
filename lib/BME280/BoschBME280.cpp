#include "Arduino.h"
#include <limits.h>
#include "Wire.h"
#include "BoschBME280.h"

bool BoschBME280::begin(uint8_t addr) {
    this->dev_addr = addr;

    // I2C configuration.
    bme280.intf = BME280_I2C_INTF;
    bme280.write = BoschBME280::I2CWrite;
    bme280.read = BoschBME280::I2CRead;
    bme280.delay_us = BoschBME280::delay_us;
    bme280.intf_ptr = &this->dev_addr;
    
    // Oversampling configuration.
    bme280.settings.osr_h = BME280_OVERSAMPLING_1X;
    bme280.settings.osr_p = BME280_NO_OVERSAMPLING;
    bme280.settings.osr_t = BME280_OVERSAMPLING_1X;
    bme280.settings.filter = BME280_FILTER_COEFF_OFF;

    Wire.begin();

    // Initialize the sensor, apply the configuration and set the sensor to FORCED mode.
    errors += bme280_init(&bme280) != BME280_OK;
    errors += (bme280_set_sensor_settings(BME280_OSR_TEMP_SEL|BME280_OSR_HUM_SEL|BME280_FILTER_SEL, &bme280) != BME280_OK) << 1;
    errors += (bme280_set_sensor_mode(BME280_FORCED_MODE, &bme280) != BME280_OK) << 2;
    req_delay = bme280_cal_meas_delay(&bme280.settings);

    return errors == 0;
}

bool BoschBME280::measure() {
    if (errors != 0) {
        return false;
    }

    errors += (bme280_set_sensor_mode(BME280_FORCED_MODE, &bme280) != BME280_OK) << 3;
    bme280.delay_us(req_delay, NULL);
    errors += (bme280_get_sensor_data(BME280_ALL, &comp_data, &bme280) != BME280_OK) << 4;

    return errors == 0;
}

double BoschBME280::getTemperature() {
    return comp_data.temperature;
}

double BoschBME280::getHumidity() {
    return comp_data.humidity;
}

int8_t BoschBME280::I2CWrite(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {  
    Wire.beginTransmission(*(uint8_t*)intf_ptr);

    Wire.write(reg_addr);
    Wire.write(reg_data, len);
    Wire.endTransmission();

    return BME280_OK;
}

int8_t BoschBME280::I2CRead(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    Wire.beginTransmission(*(int*)intf_ptr);

    Wire.write(reg_addr);
    Wire.endTransmission();

    Wire.requestFrom(*(uint8_t*)intf_ptr, len);

    uint8_t available = Wire.available();
    if(available != len) {
        Wire.flush();
        return BME280_E_COMM_FAIL;
    }

    for(uint8_t i = 0; i < available; i++) {
        *(reg_data + i) = Wire.read();
    }

    return BME280_OK;
}

void BoschBME280::delay_us(uint32_t period, void *intf_ptr) {
    delayMicroseconds(period);
}

