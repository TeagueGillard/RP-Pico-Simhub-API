# RP Pico Simhub API

### Conversion of the Simhub Arduino Pro Micro example firmware for Raspberry Pi Pico and Pico2 boards.

## Guide:

* Please follow [THIS](https://manual.simhubdash.com/standard-firmware-builder/firmware-introduction) guide until you reach the manual compilation section, at which point you will need to copy your settings over to this Arduino project file. You need to copy only the parameter for each setting.

* DO NOT COPY THE ENTIRE DOCUMENT, as this will overwrite the conversion and will not be compatible with RP Pi Pico boards.

* You do not need to create a custom board, as that is included within the sketch, and you can set your Device name, manufacturer, VID and PID all within the "RPPicoSimhubStandardDriver" tab of the sketch.

* When uploading, set your board to the correct board under "Tools > Board > Raspberry Pi Pico/RP2040/RP2350" > SELECT YOUR BOARD HERE (e.g. "Raspberry Pi Pico")

* Ensure you have "Adafruit Tiny USB" set as the USB stack under "Tools > USB Stack: > Adafruit Tiny USB"

* If you do not see the "Raspberry Pi Pico/RP2040/RP2350" or the "USB Stack:" option under the "Tools" tab, then please reinstall the arduino-pico library by earlephilhower.

If you wish to add any custom code, please feel free to add your code within:

* Core One Setup : Setup()

  // Please leave the existing code within Setup() alone as it is vital for Simhub comunication.
* Core One Loop : Loop()

  // Please ensure that "processCommands();" is left untouched within "Loop()", DO NOT move it to "Loop1()" as it will not be able to comunicate with Simhub correctly.
* Core Two Setup : Setup1
* Core Two Loop : Loop1()

## Requires: 
The "Adafruit Neo Pixel Library" library by Adafruit, available [HERE](https://github.com/adafruit/Adafruit_NeoPixel)

The "Adafruit Tiny USB Library" library by Adafruit, available [HERE](https://github.com/adafruit/Adafruit_TinyUSB_Arduino)

The "arduino-pico" library by earlephilhower, available [HERE](https://github.com/earlephilhower/arduino-pico)
