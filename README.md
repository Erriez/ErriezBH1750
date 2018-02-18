# BH1750 light sensor library for Arduino

This is a GY-302 breakout with an I2C BH1750 digital light sensor:

![BH1750](https://raw.githubusercontent.com/Erriez/ErriezBH1750/master/extras/BH1750.png)

This library supports the following features:

- Measurement in LUX
- Three operation modes:
  - Continues conversion
  - One-time conversion
- Three resolutions:
  - Low 4 LUX resolution (low power)
  - High 1 LUX resolution
  - High 0.5 LUX resolution
- Asynchronous and synchronous conversion
- Conversion timing:
  - Max 24ms low resolution
  - Max 180ms high resolution

## Hardware

![Schematic BH1750 and Arduino UNO](https://raw.githubusercontent.com/Erriez/ErriezBH1750/master/extras/BH1750_Arduino_UNO.png)

**Connection BH1750 - Arduino UNO**

| BH1750 |                         Arduino UNO                          |
| :----: | :----------------------------------------------------------: |
|  GND   |                             GND                              |
|  VCC   |                         5V (or 3.3V)                         |
|  SDA   |                              A4                              |
|  SCL   |                              A5                              |
|  ADDR  | **LOW** for I2C address **0x23** (0x46 including R/W bit)<br />**HIGH** for I2C address **0x5C** (0xB8 including R/W bit) |

**Note:** ADDR pin may be floating (open) which is the same as LOW.

**Hardware specifications**

- Two wire I2C interface
- 3.3V .. 5V compatible
- Power down (max 1.0 uA according to the datasheet)

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



## Example continues conversion high resolution

```c++
#include <Wire.h>
#include <BH1750.h>

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
#include <BH1750.h>

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

### Wait for completion asynchronously

The sensor conversion completion status can be checked asynchronously (non-blocking) before reading the light value:

```c++
bool completed = sensor.isConversionCompleted();
```

### Wait for completion synchronously

The sensor conversion completion status can be checked synchronously (blocking) before reading the light value:

```c++
// Wait for completion
// completed = false: Timeout or device in power-down
bool completed = sensor.waitForCompletion();
```

### Read light value in LUX

**One-time mode:** The application must wait or check for a completed conversion, otherwise the sensor may return an invalid value. 
**Continues mode:** The application can call this function without checking completion, but is not recommended when accurate values are required.

The sensor light value can be read when the conversion is completed:

```c++
// lux = 0: No light or not initialized
uint16_t lux = sensor.read();
```
For low and medium resolution:

```c++
// Print low and medium resolutions
Serial.print(F("Light: "));
Serial.print(lux);
Serial.println(F(" LUX"));
```

For high resolution:

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

A manual power-down in continues mode can be generated with:

```c++
powerDown();
```


