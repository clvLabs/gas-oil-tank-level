#pragma once

// Serial output (comment to disable)
// #define SERIAL_OUTPUT_ENABLED

// Distance sensor
#define DISTANCE_SENSOR_PIN ( A0 )

// Display
#define DISPLAY_CLASS       U8GLIB_SSD1306_128X64
#define DISPLAY_WIDTH       ( 128 )
#define DISPLAY_HEIGHT      ( 64 )
#define DISPLAY_MINX        ( 0 )
#define DISPLAY_MINY        ( 0 )
#define DISPLAY_MAXX        ( DISPLAY_MINX + DISPLAY_WIDTH - 1 )
#define DISPLAY_MAXY        ( DISPLAY_MINY + DISPLAY_HEIGHT - 1 )

// Level calibration
#define DIST2FLOOR_CM   ( 120 )
#define BASEMARGIN_CM   (   5 )

#define BOTTOM_CM       ( DIST2FLOOR_CM - BASEMARGIN_CM )
#define MINTOPREAD_CM   (  30 ) // ????
#define TOP_CM          ( MINTOPREAD_CM )
#define TANK_HEIGHT_CM  ( BOTTOM_CM - TOP_CM )

// Low battery alarm
// #define LOWBATT_PANIC_MODE_THRESHOLD_MV  ( 4800 )  // 4.800V
#define LOWBATT_PANIC_MODE_THRESHOLD_MV  ( 2000 )  // 2.000V

// Blink timing
#define BLINK_ON_TIME ( 1000 )
#define BLINK_OFF_TIME ( 500 )
