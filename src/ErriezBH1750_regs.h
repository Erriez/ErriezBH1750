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
 * \file ErriezBH1750_regs.h
 * \brief BH1750 digital light sensor library for Arduino.
 * \details
 *     Source:          https://github.com/Erriez/ErriezBH1750
 *     Documentation:   https://erriez.github.io/ErriezBH1750
 */

#ifndef ERRIEZ_BH1750_REGS_H_
#define ERRIEZ_BH1750_REGS_H_

// I2C addresses (without R/W bit)
#define BH1750_I2C_ADDR_L       0x23  //!< I2C address with ADDR pin low
#define BH1750_I2C_ADDR_H       0x5C  //!< I2C address with ADDR pin high

// Instructions
#define BH1750_POWER_DOWN       0x00  //!< Power down instruction
#define BH1750_POWER_ON         0x01  //!< Power on instruction
#define BH1750_RESET            0x07  //!< Reset instruction

// Bitfields
#define BH1750_MODE_MASK        0x30  //!< Mode mask bits
#define BH1750_RES_MASK         0x03  //!< Mode resolution mask bits

// Worst case conversion timing in ms
#define BH1750_CONV_TIME_L      24    //!< Worst case conversion timing low res
#define BH1750_CONV_TIME_H      180   //!< Worst case conversion timing high res

/*!
 * \def IS_INITIALIZED(mode)
 *      Return if mode is set (initialized)
 */
#define IS_INITIALIZED(mode)    (((mode) & BH1750_MODE_MASK) != 0x00)

/*!
 * \def IS_CONTINUES_MODE(mode)
 *      Macro is continues mode enabled
 */
#define IS_CONTINUES_MODE(mode) (((mode) & BH1750_MODE_MASK) == ModeContinuous)

/*!
 * \def IS_ONE_TIME_MODE(mode)
 *      Macro is one-time mode enabled from mode
 */
#define IS_ONE_TIME_MODE(mode)  (((mode) & BH1750_MODE_MASK) == ModeOneTime)

/*!
 * \def IS_LOW_RESOLUTION(mode)
 *      Macro is low resolution enabled from mode
 */
#define IS_LOW_RESOLUTION(mode) (((mode) & BH1750_RES_MASK) == ResolutionLow)

/*!
 * \def GET_TIMEOUT(mode)
 *      Macro low/high resolution timeout from mode
 */
#define GET_TIMEOUT(mode)       ((((mode) & BH1750_RES_MASK) == ResolutionLow) ? \
                                  BH1750_CONV_TIME_L : BH1750_CONV_TIME_H)

#endif // ERRIEZ_BH1750_REGS_H_
