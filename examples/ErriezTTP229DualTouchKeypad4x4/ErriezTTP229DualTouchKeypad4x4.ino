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

/*!
 * \brief Erriez TTP229 touch sensitive 4x4 keypad dual example for Arduino
 * \details
 *      Source:         https://github.com/Erriez/ErriezTTP229TouchKeypad
 *      Documentation:  https://erriez.github.io/ErriezTTP229TouchKeypad
 */

#include <ErriezTTP229.h>

// Connect SCL to any DIGITAL pin
// Connect SDO to pin with interrupt support:
//
// +-----------------------------------+----------------------------+
// |              Board                |    DIGITAL interrupt pins  |
// +-----------------------------------+----------------------------+
// | Uno, Nano, Mini, other 328-based  |  2, 3                      |
// | Mega, Mega2560, MegaADK           |  2, 3, 18, 19, 20, 21      |
// | Micro, Leonardo, other 32u4-based |  0, 1, 2, 3, 7             |
// | ESP8266/ESP32)                    |  Any                       |
// +-----------------------------------+----------------------------+
//

// TTP229 pin defines
#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_SAM_DUE)
#define TTP229_1_SDO_PIN    2  // SDO keypad 1 to pin 2 (INT0) or 3 (INT1)
#define TTP229_2_SDO_PIN    3  // SDO keypad 2 to pin 2 (INT0) or 3 (INT1)
#define TTP229_SCL_PIN      4  // SCL keypad 1 and 2 parallel to any pin
#elif defined(ARDUINO_ARCH_ESP8266)
#define TTP229_1_SDO_PIN   D1  // SDO keypad 1 to any interrupt pin
#define TTP229_2_SDO_PIN   D2  // SDO keypad 2 to any interrupt pin
#define TTP229_SCL_PIN     D3  // SCL keypad 1 and 2 parallel to any pin
#elif defined(ARDUINO_ARCH_ESP32)
#define TTP229_1_SDO_PIN   16  // SDO keypad 1 to any interrupt pin
#define TTP229_2_SDO_PIN   17  // SDO keypad 2 to any interrupt pin
#define TTP229_SCL_PIN      4  // SCL keypad 1 and 2 parallel to any pin
#else
#error "May work, but not tested on this target"
#endif

// Create two keypad objects
ErriezTTP229 ttp229[2];


#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif
void key1Change()
{
    ttp229[0].keyChange = true;
}

#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif
void key2Change()
{
    ttp229[1].keyChange = true;
}

void setup()
{
    // Initialize serial
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.println(F("\nErriez TTP229 dual 16-keys keypad example"));

    // Initialize keypad 1 with interrupt
    ttp229[0].begin(TTP229_SCL_PIN, TTP229_1_SDO_PIN);
    attachInterrupt(digitalPinToInterrupt(TTP229_1_SDO_PIN), key1Change, FALLING);

    // Initialize keypad 2 with interrupt
    ttp229[1].begin(TTP229_SCL_PIN, TTP229_2_SDO_PIN);
    attachInterrupt(digitalPinToInterrupt(TTP229_2_SDO_PIN), key2Change, FALLING);
}

void loop()
{
    uint8_t key;

    // Check if keypad 1 changed
    if (ttp229[0].keyChange) {
        Serial.println(ttp229[0].GetKey16());
        ttp229[0].keyChange = false;
    }

    // Check if keypad 2 changed
    if (ttp229[1].keyChange) {
        key = ttp229[1].GetKey16();
        Serial.println(key ? (16 + key) : 0);
        ttp229[1].keyChange = false;
    }
}