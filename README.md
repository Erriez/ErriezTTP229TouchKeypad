# Erriez TTP229 touch sensitive keypad library for Arduino

[![Build Status](https://travis-ci.org/Erriez/ErriezTTP229TouchKeypad.svg?branch=master)](https://travis-ci.org/Erriez/ErriezTTP229TouchKeypad)

This is an TTP229 touch sensitive library for Arduino.

![TTP229](https://raw.githubusercontent.com/Erriez/ErriezTTP229TouchKeypad/master/extras/TTP229TouchKeypad4x4.png)


## Library features

* 3.3V and 5V
* Two wire interface (Not I2C compatible)
* Single 4x4 touch keypad
* Dual 4x4 touch keypads
* Interrupt based
* UNO/Mini/Micro/Mega2560/Leonardo, ESP8266, ESP32 and DUE


## Design notes

* The PCB must be mounted floated, otherwise key presses don't work reliable.
* Connect pins 3 and 4 on connector P1 for 16-pin button mode.
* Smaller keypads with less pins may work, but are not tested.


## Examples

* [ErriezTTP229DualTouchKeypad4x4](https://github.com/Erriez/ErriezTTP229TouchKeypad/blob/master/examples/ErriezTTP229DualTouchKeypad4x4/ErriezTTP229DualTouchKeypad4x4.ino) Two TTP229 4x4 keypads.
* [ErriezTTP229SingleTouchKeypad4x4](https://github.com/Erriez/ErriezTTP229TouchKeypad/blob/master/examples/ErriezTTP229SingleTouchKeypad4x4/ErriezTTP229SingleTouchKeypad4x4.ino) One TTP229 4x4 keypad.


## Getting started

```c++
#include <ErriezTTP229.h>

// TTP229 pin defines
#if defined(ARDUINO_ARCH_AVR)
#define TTP229_SDO_PIN     2  // SDO to interrupt pin 2 (INT0) or pin 3 (INT1)
#define TTP229_SCL_PIN     3  // SCL to any DIGITAL IO pin
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
```

## Library dependencies

* None


## Hardware

**Arduino UNO**  
![Arduino UNO](https://raw.githubusercontent.com/Erriez/ErriezTTP229TouchKeypad/master/extras/TTP229-UNO.jpg)

**ESP8266**  
![Arduino ESP8266](https://raw.githubusercontent.com/Erriez/ErriezTTP229TouchKeypad/master/extras/TTP229-ESP8266.jpg)

**ESP32**  
![Arduino ESP32](https://raw.githubusercontent.com/Erriez/ErriezTTP229TouchKeypad/master/extras/TTP229-ESP32.jpg)

**DUE**  
![Arduino DUE](https://raw.githubusercontent.com/Erriez/ErriezTTP229TouchKeypad/master/extras/TTP229-DUE.jpg)


## Library installation

Please refer to the [Wiki](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches/wiki) page.


## Other Arduino Libraries and Sketches from Erriez

* [Erriez Libraries and Sketches](https://github.com/Erriez/ErriezArduinoLibrariesAndSketches)

