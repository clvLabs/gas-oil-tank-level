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

// Low battery alarm
// #define LOWBATT_PANIC_MODE_THRESHOLD_MV  ( 4500 )  // 4.500V
#define LOWBATT_PANIC_MODE_THRESHOLD_MV  ( 1000 )  // 1.000V

// Globals
Ultrasonic ultrasonic(DISTANCE_SENSOR_PIN);
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI


// *****************************************************************
// ***
// *** readVcc()
// ***
// *** Calculates elapsed milliseconds between actions
// ***
// *** Code from http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
// ***
// *** CHECK: https://github.com/Yveaux/arduino_vcc
// ***
long readVcc()
{
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}

void clearScreen()
{
  u8g.firstPage();
  do {} while( u8g.nextPage() );
}

void drawStrLeft(const char *str, u8g_uint_t y) {
  u8g.drawStr( DISPLAY_MINX, y, str );
}

void drawStrRight(const char *str, u8g_uint_t y) {
  u8g_uint_t strWidth = u8g.getStrWidth(str);
  u8g_uint_t x = DISPLAY_MINX + ( DISPLAY_WIDTH - strWidth );

  u8g.drawStr( x, y, str );
}

void drawStrCentered(const char *str, u8g_uint_t y) {
  u8g_uint_t strWidth = u8g.getStrWidth(str);
  u8g_uint_t x = DISPLAY_MINX + ( (DISPLAY_WIDTH - strWidth) / 2 );

  u8g.drawStr( x, y, str );
}

void formatDecimals(char* buf, long val, int decimals, const char* suffix) {
    int intPart = val / decimals;
    int decimalPart = val % decimals;
    sprintf( buf, "%d.%d%s", intPart, decimalPart, suffix );
}

void updateUI(long cm) {
  long distFromBottom = BOTTOM_CM - cm;
  char lcDistanceStr[20];
  char lcPctStr[20];
  char lcBattVoltsStr[20];
  int barPixels = -1;

  sprintf( lcDistanceStr, "%ldcm", cm );

  if (distFromBottom < 1) {
    sprintf( lcPctStr, "+%ld!!", (distFromBottom*-1) );
  } else {
    long fillFactor = (distFromBottom * 1000) / TANK_HEIGHT_CM;
    formatDecimals( lcPctStr, fillFactor, 10, "%" );

    barPixels = ( DISPLAY_WIDTH * fillFactor ) / 1000;
  }

  long batteryVoltage = readVcc() / 100; // Just 1 decimal
  formatDecimals( lcBattVoltsStr, batteryVoltage, 10, "V" );

  Serial.print(lcPctStr);
  Serial.print(" - ");
  Serial.print(lcDistanceStr);
  Serial.print(" - ");
  Serial.print(lcBattVoltsStr);
  Serial.println();

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_fub30r);
    drawStrCentered( lcPctStr, 32 );

    if (barPixels != -1) {
      u8g.drawBox( DISPLAY_MINX+1, 38, barPixels-1, 8 );
    }

    u8g.setFont(u8g_font_fub11r);
    drawStrLeft( lcDistanceStr, DISPLAY_MAXY );
    drawStrRight( lcBattVoltsStr, DISPLAY_MAXY );

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
