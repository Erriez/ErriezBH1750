/*
 * MIT License
 *
 * Copyright (c) 2020 Erriez
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
 * \file ErriezBH1750.cpp
 * \brief BH1750 digital light sensor library for Arduino.
 * \details
 *     Source:          https://github.com/Erriez/ErriezBH1750
 *     Documentation:   https://erriez.github.io/ErriezBH1750
 */

#include "ErriezBH1750.h"
#include "ErriezBH1750_regs.h"

/*!
 * \brief
 *      Constructor
 * \param addrPinLevel
 *      Sensor I2C address:
 *          ADDR pin = LOW:  0x23 (default)
 *          ADDR pin = HIGH: 0x5C
 */
BH1750::BH1750(uint8_t addrPinLevel) : _completionTimestamp(0)
{
    if (addrPinLevel == HIGH) {
        _i2cAddr = BH1750_I2C_ADDR_H;
    } else {
        _i2cAddr = BH1750_I2C_ADDR_L;
    }
}

/*!
 * \brief
 *     Set mode and resolution
 * \param mode
 *     ModeContinuous for continues mode
 *         Continues conversion requires more power
 *     ModeOneTime for one-time conversion mode
 *         Set in low power when conversion completed
 * \param resolution
 *     Resolution05Lux for high resolution (max 180ms conversion)
 *     Resolution1Lux for normal resolution (max 180ms conversion)
 *     Resolution4Lux for low resolution  (max 24ms conversion, low power)
 */
void BH1750::begin(BH1750_Mode_e mode, BH1750_Resolution_e resolution)
{
    // Store mode and resolution in variable.
    // Mode will be send in startConversion()
    _mode = (mode & BH1750_MODE_MASK) | (resolution & BH1750_RES_MASK);

    // Power down
    powerDown();
}

/*!
 * \brief
 *     Power down. Call startConversion() to power-up automatically.
 */
void BH1750::powerDown()
{
    _completionTimestamp = 0;
    writeInstruction(BH1750_POWER_DOWN);
}

/*!
 * \brief
 *     Start conversion.
 */
void BH1750::startConversion()
{
    if (IS_INITIALIZED(_mode)) {
        writeInstruction(_mode);
        setTimestamp();
    }
}

/*!
 * \brief
 *      Wait for completion
 * \return
 *      true: Conversion completed
 *      false: Conversion busy
 */
bool BH1750::isConversionCompleted()
{
    if (IS_INITIALIZED(_mode) == false) {
        return false;
    }

    if (_completionTimestamp && (millis() >= _completionTimestamp)) {
        return true;
    } else {
        return false;
    }
}

/*!
 * \brief
 *      Wait for completion
 * \return
 *      true: Conversion completed
 *      false: Not initialized, or timeout
 */
bool BH1750::waitForCompletion()
{
    uint8_t timeout;

    if (IS_INITIALIZED(_mode) == false) {
        return false;
    }

    if (IS_LOW_RESOLUTION(_mode) == true) {
        timeout = BH1750_CONV_TIME_L;
    } else {
        timeout = BH1750_CONV_TIME_H;
    }

    // Check if conversion completed in a loop
    // Wait additional 2m
    for (uint8_t i = 0; i < (timeout + 2); i++) {
        if (isConversionCompleted()) {
            return true;
        }
        delay(1);
    }

    return false;
}

/*!
 * \brief
 *      Read light level asynchronous from sensor
 *      The application is responsible for wait or checking a completed
 *      conversion, otherwise the last conversion value may be returned which
 *      may not be correct.
 *      The last value is also returned when the device is in power-down.
 * \return
 *      Light level in lux (0..65535)
 *      In high resolution, the last digit is the remainder
  */
uint16_t BH1750::read()
{
    uint16_t level;

    // Check operation mode
    if (IS_INITIALIZED(_mode) == false) {
        return 0;
    }

    if (IS_ONE_TIME_MODE(_mode)) {
        // Clear conversion in one-time mode
        // Application should call startConversion() again
        _completionTimestamp = 0;
    } else if (IS_CONTINUES_MODE(_mode)) {
        setTimestamp();
    }

    // Read two bytes from sensor
    Wire.requestFrom((int) _i2cAddr, 2);

    // Read low and high bytes
    level = (uint16_t) Wire.read();
    level <<= 8;
    level |= (uint8_t) Wire.read();

    //level = 0b1000001110010000; // 28067 lx
    //level = 0b0000000100010000; // 227 lx
    //level = 0b0000000000010010; // 7.5 lx

    // Convert raw value to LUX
    level = ((((uint32_t) level) * 10) + 5) / 12;

    return level;
}

//------------------------------------------------------------------------------
// Protected functions
//------------------------------------------------------------------------------
/*!
 * \brief
 *     Save current time + minimum delay before reading next conversion in ms
 */
void BH1750::setTimestamp()
{
    _completionTimestamp = millis() + GET_TIMEOUT(_mode);
}

/*!
 * \brief
 *      Write instruction to sensor
 * \param instruction
 *      Sensor instruction
 */
void BH1750::writeInstruction(uint8_t instruction)
{
    Wire.beginTransmission(_i2cAddr);
    Wire.write(instruction);
    Wire.endTransmission();
}
