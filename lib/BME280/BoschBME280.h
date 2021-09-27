#pragma once

#include <bme280.h>

class BoschBME280 {
    public:
        bool begin(uint8_t addr=0x76);
        bool measure();

        double getTemperature();
        double getHumidity();
        double getPressure();
    private:
        static int8_t I2CRead(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
        static int8_t I2CWrite(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
        static void delay_us(uint32_t period, void *intf_ptr);

        // TODO - debug why when errors is moved at top below the code is crashing.
        uint8_t dev_addr;
        uint32_t req_delay;
        uint8_t errors = 0;
        struct bme280_dev bme280;
        struct bme280_data comp_data;
};
