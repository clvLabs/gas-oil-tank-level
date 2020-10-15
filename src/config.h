#pragma once

#include "Arduino.h"

// Program EEPROM signature
static const int PROGRAM_EEPROM_SIGNATURE = 3014;

// Serial output (comment to disable)
// #define SERIAL_OUTPUT_ENABLED

// Distance sensor
static const uint8_t PING_TRIGGER_PIN = A0;
static const uint8_t PING_ECHO_PIN = A1;
static const unsigned int PING_MAX_DISTANCE = 500; // See NewPing.h

// Main loop sleep
static const int LOOP_SLEEP_MS = 10;

// Buttons
static const uint8_t BUTTON_DEBOUNCE_MS = 25;
static const bool BUTTON_INTERNAL_PULLUP = false;
static const bool BUTTON_INVERT = false;
static const int BUTTON_HOLD_TIME = 2000;
static const int BUTTON_RAMP1_TIME = 500;
static const int BUTTON_RAMP2_TIME = 4000;

static const uint8_t BUTTON_UP_PIN = 3;
static const uint8_t BUTTON_DOWN_PIN = 4;

// Display
#define DISPLAY_CLASS U8GLIB_SSD1306_128X64
static const int DISPLAY_WIDTH = 128;
static const int DISPLAY_HEIGHT = 64;
static const int DISPLAY_MINX = 0;
static const int DISPLAY_MINY = 0;
static const int DISPLAY_MAXX = DISPLAY_MINX + DISPLAY_WIDTH - 1;
static const int DISPLAY_MAXY = DISPLAY_MINY + DISPLAY_HEIGHT - 1;

// Level calibration
static const unsigned int MIN_LEVEL_CM_DEFAULT = 119;
static const unsigned int MAX_LEVEL_CM_DEFAULT = 27;

// Low battery alarm
static const long LOWBATT_PANIC_MODE_THRESHOLD_MV = 2000; // 2.000V

// Blink timing
static const unsigned int BLINK_ON_TIME = 500;
static const unsigned int BLINK_OFF_TIME = 500;
