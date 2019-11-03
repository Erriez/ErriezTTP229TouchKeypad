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

#include <ErriezTTP229.h>

#define TTP229_1_SDO_PIN    2  // SDO keypad 1 to pin 2 (INT0) or 3 (INT1)
#define TTP229_2_SDO_PIN    3  // SDO keypad 2 to pin 2 (INT0) or 3 (INT1)
#define TTP229_SCL_PIN      4  // SCL keypad 1 and 2 parallel to any pin


static ErriezTTP229 ttp229[2];


void key1Change()
{
    ttp229[0].keyChange = true;
}

void key2Change()
{
    ttp229[1].keyChange = true;
}

void setup()
{
    Serial.begin(115200);
    Serial.println(F("TTP229 dual 16-keys keypad example"));
    
    ttp229[0].begin(TTP229_SCL_PIN, TTP229_1_SDO_PIN);
    pinMode(TTP229_1_SDO_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(TTP229_1_SDO_PIN), key1Change, FALLING);

    ttp229[1].begin(TTP229_SCL_PIN, TTP229_2_SDO_PIN);
    pinMode(TTP229_2_SDO_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(TTP229_2_SDO_PIN), key2Change, FALLING);
}

void loop()
{
    uint8_t key;

    if (ttp229[0].keyChange) {
        Serial.println(ttp229[0].GetKey16());
        ttp229[0].keyChange = false;
    }
    if (ttp229[1].keyChange) {
        key = ttp229[1].GetKey16();
        Serial.println(key ? (16 + key) : 0);
        ttp229[1].keyChange = false;
    }
}