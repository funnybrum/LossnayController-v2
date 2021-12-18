#pragma once

#include "BoschBME280.h"

#define BME280_READ_INTERVAL 1000

struct BME280Settings {
    int16_t temperatureFactor;    // In 0.01 units, i.e. 100 here sets the factor to 1
    int8_t temperatureOffset;  // In 0.1C
    int16_t humidityFactor;    // In 0.01 units, i.e. 100 here sets the factor to 1
    int8_t humidityOffset;     // In 0.1%
};

const char BME280_CONFIG_PAGE[] PROGMEM = R"=====(
<fieldset style='display: inline-block; width: 300px'>
<legend>%s</legend>
<small>Used for precise sensor calibration<br>corrected = 0.01*factor*raw + 0.1*offset</small><br>
Temperature factor:<br>
<input type="text" name="%stemp_factor" value="%d"><br>
Temperature offset:<br>
<input type="text" name="%stemp_offset" value="%d"><br>
<small><em>in 0.1 degrees, from -125 to 125</em></small><br>
<br>
Humidity factor:<br>
<input type="text" name="%shumidity_factor" value="%d"><br>
Humidity offset:<br>
<input type="text" name="%shumidity_offset" value="%d"><br>
</fieldset>
)=====";

class BME280 {
    public:
        BME280(BME280Settings* settings, uint8_t address=0x76, const char* prefix="", const char* legend="BME280");
        bool begin();
        void loop();
        bool measure();

        float getTemperature();
        float getHumidity();
        float getPressure();
        float getAbsoluteHimidity();

        void get_config_page(char* buffer);
        void parse_config_params(WebServerBase* webServer);

    private:
        float rh_to_ah(float rh, float temp);

        float _temp;
        float _humidity;
        float _pressure;
        bool _sensorFound;
        bool _initialized = false;
        uint8_t _address;
        char _prefix[5];
        char _legend[24];
        uint32_t _lastMeasure;
        BoschBME280 _bme280 = BoschBME280();
        BME280Settings* _settings;
};
