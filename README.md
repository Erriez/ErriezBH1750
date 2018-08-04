# BH1750 digital light sensor library for Arduino

[![Build Status](https://travis-ci.org/Erriez/ErriezBH1750.svg?branch=master)](https://travis-ci.org/Erriez/ErriezBH1750)

This is a 16-bit BH1750 digital ambient light sensor on a GY-302 breakout PCB:

![BH1750](https://raw.githubusercontent.com/Erriez/ErriezBH1750/master/extras/BH1750.png)

## Arduino library features

- Measurement in LUX
- Three operation modes:
  - Continues conversion
  - One-time conversion
- Three selectable resolutions:
  - Low 4 LUX resolution (low power)
  - High 1 LUX resolution
  - High 0.5 LUX resolution
- Asynchronous and synchronous conversion


## BH1750 sensor specifications

- Operating voltage: 3.3V .. 4.5V max
- Low current by power down: max 1uA
- I2C bus interface: max 400kHz
- Ambience light:
  - Range: 1 - 65535 lx
  - Deviation: +/- 20%
  - Selectable resolutions:
    - 4 lx (low resolution, max 24 ms measurement time)
    - 1 lx (mid resolution max 180 ms measurement time)
    - 0.5 lx (high resolution 180 ms measurement time)
- No additional electronic components needed


## GY-302 breakout specifications

- Supply voltage: 3.3 .. 5V
- 5V tolerant I2C SCL and SDA pins
- 2 selectable I2C addresses with ADDR pin high or low/floating


## Hardware

![Schematic BH1750 and Arduino UNO](https://raw.githubusercontent.com/Erriez/ErriezBH1750/master/extras/BH1750_Arduino_UNO.png)

**Connection BH1750 - Arduino / ESP8266 boards**

| BH1750 | Arduino UNO / Nano | Leonardo / Pro Micro |   Mega2560   | WeMos D1 & R2 / Node MCU | WeMos LOLIN32 |
| :----: | :----------------: | :------------------: | :----------: | :----------------------: | :-----------: |
|  GND   |        GND         |         GND          |     GND      |           GND            |      GND      |
|  VCC   |    5V (or 3.3V)    |     5V (or 3.3V)     | 5V (or 3.3V) |           3V3            |      3V3      |
|  SDA   |  A4 (ANALOG pin)   |   2 (DIGITAL pin)    |     D20      |            D2            |       5       |
|  SCL   |  A5 (ANALOG pin)   |   3 (DIGITAL pin)    |     D21      |            D1            |       4       |

Other MCU's may work, but are not tested.

#### WeMos LOLIN32 with OLED display

Change the following Wire initialization to:

```c++
// WeMos LOLIN32 with OLED support
Wire.begin(5, 4);
```

### I2C address

* ```ADDR``` pin ```LOW ``` for I2C address 0x23 (0x46 including R/W bit)

* ```ADDR``` pin ```HIGH``` for I2C address 0x5C (0xB8 including R/W bit)

**Note:** ```ADDR``` pin may be floating (open) which is the same as LOW.

## Examples

Examples | Erriez BH1750:

* ContinuesMode | [BH1750ContinuesAsynchronous](https://github.com/Erriez/ErriezBH1750/blob/master/examples/ContinuesMode/BH1750ContinuesAsynchronous/BH1750ContinuesAsynchronous.ino)
* ContinuesMode | [BH1750ContinuesBasic](https://github.com/Erriez/ErriezBH1750/blob/master/examples/ContinuesMode/BH1750ContinuesBasic/BH1750ContinuesBasic.ino)
* ContinuesMode | [BH1750ContinuesHighResolution](https://github.com/Erriez/ErriezBH1750/blob/master/examples/ContinuesMode/BH1750ContinuesHighResolution/BH1750ContinuesHighResolution.ino)
* ContinuesMode | [BH1750ContinuesLowResolution](https://github.com/Erriez/ErriezBH1750/blob/master/examples/ContinuesMode/BH1750ContinuesLowResolution/BH1750ContinuesLowResolution.ino)
* ContinuesMode | [BH1750ContinuesPowerMgt](https://github.com/Erriez/ErriezBH1750/blob/master/examples/ContinuesMode/BH1750ContinuesPowerMgt/BH1750ContinuesPowerMgt.ino)
* OneTimeMode | [BH1750OneTimeBasic](https://github.com/Erriez/ErriezBH1750/blob/master/examples/OneTimeMode/BH1750OneTimeBasic/BH1750OneTimeBasic.ino)
* OneTimeMode| [BH1750OneTimeHighResolution](https://github.com/Erriez/ErriezBH1750/blob/master/examples/OneTimeMode/BH1750OneTimeHighResolution/BH1750OneTimeHighResolution.ino)
* OneTimeMode| [BH1750OneTimeLowResolution](https://github.com/Erriez/ErriezBH1750/blob/master/examples/OneTimeMode/BH1750OneTimeLowResolution/BH1750OneTimeLowResolution.ino)
* OneTimeMode| [BH1750OneTimePowerMgt](https://github.com/Erriez/ErriezBH1750/blob/master/examples/OneTimeMode/BH1750OneTimePowerMgt/BH1750OneTimePowerMgt.ino)


## Documentation

- [Doxygen online HTML](https://erriez.github.io/ErriezBH1750)
- [Doxygen PDF](https://github.com/Erriez/ErriezBH1750/raw/gh-pages/latex/ErriezBH1750.pdf)
- [BH1750 chip datasheet](https://github.com/Erriez/ErriezBH1750/raw/master/extras/BH1750_datasheet.pdf)


## Example continues conversion high resolution

```c++
#include <Wire.h>
#include <ErriezBH1750.h>

// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);

void setup()
{
  Serial.begin(115200);
  Serial.println(F("BH1750 continues measurement high resolution example"));

  // Initialize I2C bus
  Wire.begin();

  // Initialize sensor in continues mode, high 0.5 lx resolution
  sensor.begin(ModeContinuous, ResolutionHigh);

  // Start conversion
  sensor.startConversion();
}

void loop()
{
  uint16_t lux;

  // Wait for completion (blocking busy-wait delay)
  if (sensor.isConversionCompleted()) {
    // Read light
    lux = sensor.read();

    // Print light
    Serial.print(F("Light: "));
    Serial.print(lux / 2);
    Serial.print(F("."));
    Serial.print(lux % 10);
    Serial.println(F(" LUX"));
  }
}
```
**Output**
```c++
BH1750 continues measurement high resolution example
Light: 15.0 LUX
Light: 31.2 LUX
Light: 385.0 LUX
Light: 575.1 LUX
Light: 667.5 LUX
```

## Usage

### Initialization

```c++
#include <Wire.h>
#include <ErriezBH1750.h>

// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);

void setup()
{
  	// Initialize I2C bus
  	Wire.begin();
    
    // Initialize sensor with a mode and resolution:
    //   Modes:
    //     ModeContinuous
    //     ModeOneTime
    //   Resolutions:
    //     ResolutionLow (4 lx resolution)
    //     ResolutionMid (1 lx resolution)
    //     ResolutionHigh (0.5 lx resolution)
    sensor.begin(mode, resolution);
}
```

### Start conversion

```Wire.begin();``` and ```sensor.begin();``` must be called before starting the conversion:

```c++
sensor.startConversion();
```

### Wait for completion asynchronous (non-blocking)

The sensor conversion completion status can be checked asynchronously before reading the light value:

```c++
bool completed = sensor.isConversionCompleted();
```

### Wait for completion synchronous (blocking)

The sensor conversion completion status can be checked synchronously before reading the light value:

```c++
// Wait for completion
// completed = false: Timeout or device in power-down
bool completed = sensor.waitForCompletion();
```

### Read light value in LUX

**One-time mode:** The application must wait or check for a completed conversion, otherwise the sensor may return an invalid value. 
**Continues mode:** The application can call this function without checking completion, but is not recommended when accurate values are required.

Read sensor light value:

```c++
// lux = 0: No light or not initialized
uint16_t lux = sensor.read();
```
For 4 lx low and 1 lx high resolutions:

```c++
// Print low and medium resolutions
Serial.print(F("Light: "));
Serial.print(lux);
Serial.println(F(" LUX"));
```

For 0.5 lx high resolution:

```c++
// Print high resolution
Serial.print(F("Light: "));
Serial.print(lux / 2);
Serial.print(F("."));
Serial.print(lux % 10);
Serial.println(F(" LUX"));
```

### Power down

The device enters power down automatically after a one-time conversion.

A manual power-down in continues mode can be generated by calling:

```c++
sensor.powerDown();
```

## Library dependencies

- Built-in ```Wire.h```


## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)

