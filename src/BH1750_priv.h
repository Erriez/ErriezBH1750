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
 * \file
 *     BH1750_priv.h
 * \brief
 *     BH1750 digital light sensor library for Arduino.
 * \details
 *     Source: https://github.com/Erriez/ErriezBH1750
 */

#ifndef BH1750_PRIV_H__
#define BH1750_PRIV_H__

// I2C addresses
#define BH1750_I2C_ADDR_L       0x23
#define BH1750_I2C_ADDR_H       0x5C

// Instructions
#define BH1750_POWER_DOWN       0x00
#define BH1750_POWER_ON         0x01
#define BH1750_RESET            0x07

// Bitfields
#define BH1750_MODE_MASK        0x30
#define BH1750_RES_MASK         0x03

// Worst case conversion timing
#define BH1750_CONV_TIME_L      24
#define BH1750_CONV_TIME_H      180

// Macro's
#define IS_INITIALIZED(mode)    (((mode) & BH1750_MODE_MASK) != 0x00)
#define IS_CONTINUES_MODE(mode) (((mode) & BH1750_MODE_MASK) == ModeContinuous)
#define IS_ONE_TIME_MODE(mode)  (((mode) & BH1750_MODE_MASK) == ModeOneTime)
#define IS_LOW_RESOLUTION(mode) (((mode) & BH1750_RES_MASK) == ResolutionLow)
#define GET_TIMEOUT(mode)       ((((mode) & BH1750_RES_MASK) == ResolutionLow) ? \
                                  BH1750_CONV_TIME_L : BH1750_CONV_TIME_H)

#endif // BH1750_PRIV_H__
