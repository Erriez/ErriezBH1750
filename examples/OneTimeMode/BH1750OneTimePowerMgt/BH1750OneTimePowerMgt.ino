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

/* BH1750 digital light sensor library for Arduino.
 * Source: https://github.com/Erriez/ErriezBH1750
 */

#include <Wire.h>
#include <BH1750.h>

// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);


void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("BH1750 one-time measurement & power management example"));

    // Initialize I2C bus
    Wire.begin();

    // Initialize sensor in one-time mode, medium 1 lx resolution
    sensor.begin(ModeOneTime, ResolutionMid);
}

void loop()
{
    uint16_t lux;

    // Power on and start conversion
    sensor.startConversion();

    // Wait for completion (blocking busy-wait delay)
    if (sensor.waitForCompletion()) {
        // Read light
        lux = sensor.read();

        // Print light
        Serial.print("Light: ");
        Serial.print(lux);
        Serial.println(" lx");
    } else {
        Serial.println("Light: -");
    }

    // Device is automatically set in power-down after one-time conversion, but
    // powerDown() can be explicitly called as well
    //sensor.powerDown();

    // Implement power management and interrupt support here for low-power
    // devices instead of the delay example below
    delay(2000);
}
