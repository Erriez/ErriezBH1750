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
 * \file BH1750.h
 * \brief BH1750 digital light sensor library for Arduino.
 * \details
 *     Source:          https://github.com/Erriez/ErriezBH1750
 *     Documentation:   https://erriez.github.io/ErriezBH1750
 */

#ifndef BH1750_H__
#define BH1750_H__

#include <Arduino.h>
#include <Wire.h>

//! \brief Mode register bits
typedef enum {
    ModeContinuous = 0x10,  //!< Continues mode
    ModeOneTime = 0x20,     //!< One-time mode
} BH1750_Mode_e;

//! \brief Resolution register bits
typedef enum {
    ResolutionLow = 0x03,  //!< 4 lx resolution
    ResolutionMid = 0x00,  //!< 1 lx resolution
    ResolutionHigh = 0x01, //!< 0.5 lx resolution
} BH1750_Resolution_e;

//! \brief BH1750 class
class BH1750
{
public:
    explicit BH1750(uint8_t addrPinLevel=LOW);
    virtual void begin(BH1750_Mode_e mode, BH1750_Resolution_e resolution);
    virtual void powerDown();
    virtual void startConversion();
    virtual bool isConversionCompleted();
    virtual bool waitForCompletion();
    virtual uint16_t read();

protected:
    virtual void writeInstruction(uint8_t instruction);
    virtual void setTimestamp();

private:
    unsigned long _completionTimestamp;
    uint8_t _i2cAddr;
    uint8_t _mode;
};

#endif // BH1750_H__
