#include "Arduino.h"
#include "U8glib.h"
#include "ultrasonic.h"

// Distance sensor
#define DISTANCE_SENSOR_PIN ( A0 )

// Display
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

Ultrasonic ultrasonic(DISTANCE_SENSOR_PIN);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI

void clearScreen()
{
  u8g.firstPage();
  do {} while( u8g.nextPage() );
}

void drawStrCentered(const char *str, u8g_uint_t y) {
  u8g_uint_t strWidth = u8g.getStrWidth(str);
  u8g_uint_t x = DISPLAY_MINX + ( (DISPLAY_WIDTH - strWidth) / 2 );

  u8g.drawStr( x, y, str);
}

void updateUI(long cm) {
  long distFromBottom = BOTTOM_CM - cm;
  char lcDistanceStr[20];
  char lcPctStr[20];


  if (distFromBottom < 1) {
    sprintf( lcDistanceStr, "%ld cm", cm );
    sprintf( lcPctStr, "+%ld!!", (distFromBottom*-1) );
  } else {
    sprintf( lcDistanceStr, "%ld cm", cm );

    // Compensate lack of float
    long fillFactor = (distFromBottom * 1000) / TANK_HEIGHT_CM;
    int percent = fillFactor / 10;
    int percentDecimal = fillFactor % 10;
    sprintf( lcPctStr, "%d.%d%%", percent, percentDecimal );
  }

  Serial.println(lcPctStr);
  Serial.print(" - ");
  Serial.print(lcDistanceStr);

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_gdr30);
    drawStrCentered( lcPctStr, 32 );
    u8g.setFont(u8g_font_gdr12);
    drawStrCentered( lcDistanceStr, 32 + (DISPLAY_HEIGHT/2) );
  } while( u8g.nextPage() );
}

void setup() {
  u8g.setColorIndex(1);
  Serial.begin(9600);
}

void loop() {
  ultrasonic.DistanceMeasure();
  long distance = ultrasonic.microsecondsToCentimeters();
  updateUI(distance);
  delay(10);
}
