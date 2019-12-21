#include "Arduino.h"
#include "U8glib.h"
#include "ultrasonic.h"


// Display
#define DISPLAY_WIDTH       ( 128 )
#define DISPLAY_HEIGHT      ( 64 )
#define DISPLAY_MINX        ( 0 )
#define DISPLAY_MINY        ( 0 )
#define DISPLAY_MAXX        ( DISPLAY_WIDTH-1 )
#define DISPLAY_MAXY        ( DISPLAY_HEIGHT-1 )


Ultrasonic ultrasonic(A0);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI

void clearScreen()
{
  u8g.firstPage();
  do {} while( u8g.nextPage() );
}

void updateUI(long cm)
{
  char lcBuffer[20];
  sprintf( lcBuffer, "%ld cm", cm );

  Serial.println(lcBuffer);

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_gdr25);
    // u8g.setFont(u8g_font_fub20n);
    // u8g.setFont(u8g_font_fub30n);

    u8g.drawStr( DISPLAY_MINX, 22, lcBuffer);
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