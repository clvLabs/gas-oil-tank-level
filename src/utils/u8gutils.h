#pragma once

#include "U8glib.h"
#include "Arduino.h"
#include "config.h"

void clearScreen(DISPLAY_CLASS &u8g);
void drawStrLeft(DISPLAY_CLASS &u8g, const char *str, u8g_uint_t y);
void drawStrRight(DISPLAY_CLASS &u8g, const char *str, u8g_uint_t y);
void drawStrCentered(DISPLAY_CLASS &u8g, const char *str, u8g_uint_t y);
