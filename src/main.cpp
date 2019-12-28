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
#define DISPLAY_MAXX        ( DISPLAY_WIDTH-1 )
#define DISPLAY_MAXY        ( DISPLAY_HEIGHT-1 )

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

void updateUI(long cm)
{
  long distFromBottom = BOTTOM_CM - cm;
  char lcLine1[20];
  char lcLine2[20];


  if (distFromBottom < 1) {
    sprintf( lcLine1, "%ld cm", cm );
    sprintf( lcLine2, "+%ld!!", (distFromBottom*-1) );
  } else {
    sprintf( lcLine1, "%ld cm", cm );

    // Compensate lack of float
    long fillFactor = (distFromBottom * 1000) / TANK_HEIGHT_CM;
    int percent = fillFactor / 10;
    int percentDecimal = fillFactor % 10;
    sprintf( lcLine2, "%d.%d%%", percent, percentDecimal );
  }

  Serial.print(lcLine1);
  Serial.print(" - ");
  Serial.println(lcLine2);

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_gdr25);
    u8g.drawStr( DISPLAY_MINX, 32, lcLine1);
    u8g.drawStr( DISPLAY_MINX, 32 + (DISPLAY_HEIGHT/2), lcLine2);
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
