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
 * \brief Erriez TTP229 touch sensitive 4x4 keypad single example for Arduino
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
#define TTP229_SDO_PIN     2  // SDO to interrupt pin 2 (INT0) or pin 3 (INT1)
#define TTP229_SCL_PIN     3  // SCL to any DITITAL IO pin
#elif defined(ARDUINO_ARCH_ESP8266)
#define TTP229_SDO_PIN    D1  // Interrupt pin
#define TTP229_SCL_PIN    D2  // Any pin
#elif defined(ARDUINO_ARCH_ESP32)
#define TTP229_SDO_PIN     16  // Keep GPIO0 low during programming
#define TTP229_SCL_PIN     4
#else
#error "May work, but not tested on this target"
#endif

// Create keypad object
ErriezTTP229 ttp229;


#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif
void keyChange()
{
    // A key press changed
    ttp229.keyChange = true;
}

void setup()
{
    // Initialize serial
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    Serial.begin(115200);
    Serial.println(F("\nErriez TTP229 single 16-keys keypad example"));

    // Initialize keypad with interrupt
    ttp229.begin(TTP229_SCL_PIN, TTP229_SDO_PIN);

    // Initialize interrupt pin on SD0
    attachInterrupt(digitalPinToInterrupt(TTP229_SDO_PIN), keyChange, FALLING);
}

void loop()
{
    // Print key
    if (ttp229.keyChange) {
        Serial.println(ttp229.GetKey16());
        ttp229.keyChange = false;
    }
}