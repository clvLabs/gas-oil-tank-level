# gas-tank-level

Easy gas tank level meter using an Arduino and a *ping* sensor

## Hardware

* Arduino Nano
* Ping sensor
* OLED screen
  * 2 3K3 resistors (I2C pullups)
* 2 buttons
  * 2 10K resistors (pullups)

## Software

### Requirements

This project has been developed with PlatformIO, you can compile it with the stock Arduino IDE, but you'll have a nicer time with PlatformIO...

### Configuration

Keeping both buttons pressed for `BUTTON_HOLD_TIME` will enter configuration mode, in which you can set `MIN_LEVEL_CM` and `MAX_LEVEL_CM`. These settings will be stored on EEPROM.

To change other settings you have to edit `src/config.h`.
