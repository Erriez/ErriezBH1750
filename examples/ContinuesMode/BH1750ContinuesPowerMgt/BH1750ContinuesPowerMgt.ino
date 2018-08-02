/*
 * MIT License
 *
 * Copyright (c) 2018 Erriez
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \brief BH1750 digital light sensor example for Arduino.
 * \details
 *      Source:          https://github.com/Erriez/ErriezBH1750
 *      Documentation:   https://erriez.github.io/ErriezBH1750
 */

#include <Wire.h>
#include <BH1750.h>

// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);

// Function prototype
void printSensor();


void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("BH1750 continues measurement & power management example"));

    // Initialize I2C bus
    Wire.begin();

    // Initialize sensor in continues mode, 1 lx medium resolution
    sensor.begin(ModeContinuous, ResolutionMid);
}

void loop()
{
    Serial.println(F("Power on..."));
    sensor.startConversion();
    for (uint8_t i = 0; i < 10; i++) {
        printSensor();
    }

    Serial.println(F("Power off..."));
    sensor.powerDown();
    for (uint8_t i = 0; i < 10; i++) {
        printSensor();
    }
}

void printSensor()
{
    uint16_t lux;

    // Wait for completion (blocking busy-wait delay)
    if (sensor.waitForCompletion()) {
        // Read light
        lux = sensor.read();

        // Print light
        Serial.print(F("Light: "));
        Serial.print(lux);
        Serial.println(F(" LUX"));
    } else {
        Serial.println(F("Light: -"));
    }
}
