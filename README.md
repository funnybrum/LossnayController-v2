# Lossnay energy recovery ventilator controller v2

The controller should work with all Mitsubishi Lossnay ERVs. This has been used for more than an year now and no issues were observed.

The functionality includes:
 1) Turning on and off the device.
 2) Setting the fan speed to 1, 2, 3 or 4.
 3) Switching between Lossnay and bypass mode.
 4) Monitoring the ERV diagnostic output (operating, bypass/lossnay, error).
 5) Tracking two BME280 sensors for monitoring the supply and exhaust air temperature and humidity.
 6) API for exposing the current status (http://{...}/get).
 7) Telemetry collection and publishing to a local InfluxDB instance.

# Hardware
The PCB project is available at [EasyEDA's OSHWLab](https://oshwlab.com/funnybrum/lossnay-controller_copy). From there you can directly order the PCB at JLCPCB.

## BOM
|Designator        |Name         |Footprint        |Quantity|
|------------------|-------------|-----------------|--------|
|C1,C2,C8          |100nF        |C0603            |3       |
|C6                |10nF         |C0603            |1       |
|C7                |3.9nF        |C0603            |1       |
|C9                |10uF         |C1206            |1       |
|C10               |22uF         |C1206            |1       |
|CN17              |jst xhp-5    |JST_XH2.54_5P    |1       |
|CN26_BPS,TM2      |Taster_H     |JST_XH2.54_2P    |2       |
|D6                |SS26         |SMA              |1       |
|I2C,MONITOR       |jst xhp-4    |JST_XH2.54_4P    |2       |
|L1                |100uH        |IND-SMD_L7.3-W7.3|1       |
|L2                |100uH        |CD32             |1       |
|P2                |DG308-2.54   |DG308-2.54-6P    |1       |
|R1,R2,R3,R4,R5,R6 |430          |R0603            |6       |
|R7,R8             |4.7k         |R0603            |2       |
|R9                |6.8K         |R0603            |1       |
|R10               |100K         |R0603            |1       |
|R11               |1k           |R0603            |1       |
|R12               |2k           |R0603            |1       |
|R13               |4k           |R0603            |1       |
|R14               |560          |R0603            |1       |
|R16               |26.1K        |R0603            |1       |
|R18               |10K          |R0603            |1       |
|R31               |4.7k         |R0603            |1       |
|R32               |120          |R0603            |1       |
|U1,U2,U3,U4,U5,U10|VO1400AEF    |SOP-4            |6       |
|U7                |WEMOS D1 MINI|WEMOS D1 MINI    |1       |
|U8                |MP2307DN-LF-Z|SOP-8            |1       |
|U9                |MAX3485      |SOIC-8           |1       |

## Notes
The supply voltage should be between 5V and 24V.

The RS485 part is not yet implemented in the firmware and can be skipped. This will likely be added in future versions of the firmware.

If there are WiFi connectivity issues swap the WeMos D1 Mini for a D1 Mini Pro with the same module size. The pro has a ceramic antena and SMA connector for external antena.

# Lossnay mainboard communication
This is based on the official documentation provided by Mitshubishi. Download the "Lossnay Energy Recovery Ventilator Installation Instructions" (the file is usually named LGH-RVX_Installation_Manual.pdf) and crosscheck each connection point.

## TM2 to turn on/off the device
Based on "When interlocked with indoor unit of air conditioner or other external device including other manufactures." from the documentation, 3rd option - "When the external device has an uncharged a-contact signal".

The device must be turned on before operating it. Untill it is turned on - the speed settings have no effect. This is acomplished by one of the SSRs that connects TM2-1 to TM2-3.

The wiring diagram is (Controller <-> Lossnay):
 * TM2-1 <-> TM2-1
 * TM2-2 <-> TM2-3

## CN17 to controll the 4 fan speeds
Based on the "When switching fan speed externally" from the documentation.

This works by using the CN17 connector. There are 4 SSRs that are connecting one of the CN17-2/CN17-3/CN17-4/CN17-5 to CN17-1.

The wiring diagram is (Controller <-> Lossnay):
CN17-1 <-> CN17-1
CN17-2 <-> CN17-2
CN17-3 <-> CN17-3
CN17-4 <-> CN17-4
CN17-5 <-> CN17-5

## CN26 to controll the bypass valve
Based on the "When switching By-pass externally." from the documentation.

In some cases it would be desired to use the bypass mode to avoid heat/humidity recovery. Again achived by SSR connecting CN26-1 to CN26-2. Connecting these two will force bypass mode. Disconnecting them will set the desired mode to recovery (lossnay) mode. The HRV may decide by itself to enter bypass mode in some cases. Check the documentation for details.

The wiring diagram is (Controller <-> Lossnay):
CN26_BPS-1 <-> CN26-1
CN26_BPS-2 <-> CN26-2


## Lossnay status output
Based on the following 3 sections from the official documentation:
 * "By-pass monitor or Pre-heater signal output."
 * "Malfunction monitor output."
 * "Operation monitor output"
 
The Lossnay exposes 3 relay outputs indicating if the device is on or off, if there is a malfunction and the current mode (lossnay/bypass). The controller monitor these through the analog input and array of 3 resistors.

The wiring diagram is (Controller <-> Lossnay):
MONITOR-1 <-> TM3-7
MONITOR-2 <-> TM3-8
MONITOR-3 <-> TM3-9
MONITOR-4 <-> TM3-10

# Implementation notes

## Building the project
The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```

# Using the controller

## First boot
On first start the device will create an open WiFi network named `ventilator`. Connect to it and open http://192.168.0.1. This will bring the configuration page. Set the host name, the SSID and the password. Click "Save" and "Restart". The device will reboot, connect to the WiFi network and will be accessbile by its hostname.

## Updating the configurations
The configuration page will be available all the time. Go the http://{hostname or IP address}/ and you will get redirected to the same page that you used for the first boot.

## Exposed APIs for controlling the Mitsubishi Lossnay
### Turning on and off
 * http://{hostname or IP address}/on
 * http://{hostname or IP address}/off
 
### Setting Lossnay or bypass mode
 * http://{hostname or IP address}/mode?lossnay 
 * http://{hostname or IP address}/mode?bypass
 
### Setting the fan speed
 * http://{hostname or IP address}/speed?1
 * http://{hostname or IP address}/speed?2
 * http://{hostname or IP address}/speed?3
 * http://{hostname or IP address}/speed?4
 
### Embaded help page
 * http://{hostname or IP address}/help
 
### Device status
 * http://{hostname or IP address}/get
 
This will expose a JSON document similar to the following one, but without the comments:
```
{
  "ra_temp": 20.6,          -> return/exhaust air temperature, in C
  "ra_humidity": 49.9,      -> return/exhaust air relative humidity, in %
  "ra_pressure": 922,       -> retur/exhaust air pressure, in mbar
  "ra_abs_humidity": 8.94,  -> retur/exhaust air absolute humidity, in g/m3
  "sa_temp": 19.4,          -> supply/fresh air tempeature
  "sa_humidity": 46.9,      -> supply/fresh air humidity
  "sa_pressure": 922,       -> supplyfresh air pressure 
  "sa_abs_humidity": 7.82,  -> supply/fresh air absolute humidity
  "bypass": false,          -> current desired mode (the one set by the controller)
  "power": true,            -> Lossnay desired power status
  "fan_speed": 1,           -> Lossnay fan speed
  "analog": 965,            -> Current status on the analog input, for debuging purposes
  "i_bypass": 0,            -> Lossnay bypass status as reported by the Lossnay itself
  "i_malfunction": 0,       -> Lossnay error/malfunction indiciator as reported by the Lossnay itself
  "i_operating": 1,         -> Lossnay operating status as reported by the Lossnay itself
  "rssi": -73               -> WiFi RSSI
}```
