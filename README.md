**NOTE: WIP**

# Lossnay energy recovery ventilator controller v2

This time I got a Lossnay LGH-100RVX-E and I'm bilding improved version of the Lossnay Controller. The improvements will include:
 1) Improved REST API.
 2) PCB (shared project).
 3) External antena! Very critical part, as the old version had PCB antena that is loosing connectivityt when put inside a metal enclosure.
 4) Temeprature/humidity monitoring on the exhaust/fresh air. This was planned for v1, but never got added. BME280 will be used for that purpose.
 5) Telemetry collection (fan speed, on/off state/bypass valve).

# Lossnay mainboard communication

## TM2 to turn on/off the device

The device must be turned on before operating it. Untill it is turned on - the speed settings have no effect.

This will be implemented with optocoupler. The output of it will "ground" TM2-1 to TM2-3. The current is a few mA.


## CN17 to controll the 4 fan speeds

There are two options for that - with 0VDC to 10VDC on CN26 (pins 4 and 5) or with 4 switches on CN17. I'm choosing the second option as it looks a bit simpler to implement.

This will be achived with 4 optocoplers. Grounding any of the CN17-2, CN17-3, CN17-4 and CN17-5 to CN17-1 will control the fan speed.


## CN26 to controll the bypass valve

In some cases it would be desired to use the bypass mode to avoid heat/humidity recovery. Again - optocoupler on CN26-1 and CN26-2. Grounding CN26-2 to CN26-1 will set bypass mode. Disconnecting them will set recovery (lossnay) mode.

# Implementation notes

## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```

# Future improvements
* Add support for supply/return air pressure