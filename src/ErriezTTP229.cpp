/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Erriez
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

#include <Arduino.h>

#include "ErriezTTP229.h"


void ErriezTTP229::begin(uint8_t sclPin, uint8_t sdoPin)
{
    _sclPin = sclPin;
    _sdoPin = sdoPin;
    
    pinMode(_sclPin, OUTPUT);
    pinMode(_sdoPin, INPUT_PULLUP);
    
    digitalWrite(_sclPin, HIGH);
}

uint8_t ErriezTTP229::GetKey16()
{
    uint8_t key = 0;
    
    for (uint8_t i = 0; i < 16; i++) {
        if (GetBit()) {
            key = i + 1;
        }
    }
    delay(2); // Tout

    return key;
}

bool ErriezTTP229::GetBit()
{
    bool retVal;
    
    digitalWrite(_sclPin, LOW);
    delayMicroseconds(2); // 500KHz
    retVal = !digitalRead(_sdoPin);
    digitalWrite(_sclPin, HIGH);
    delayMicroseconds(2); // 500KHz
    
    return retVal;
}
