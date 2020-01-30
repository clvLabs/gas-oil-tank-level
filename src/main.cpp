#include "Arduino.h"
#include "U8glib.h"
#include "config.h"
#include "ultrasonic.h"
#include "readvcc.h"
#include "utils.h"
#include "u8gutils.h"

// Globals
Ultrasonic ultrasonic(DISTANCE_SENSOR_PIN);
DISPLAY_CLASS u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI
unsigned long lastBlink;
bool currentBlinkON;


void updateUI(long cm) {
  long distFromBottom = BOTTOM_CM - cm;
  char lcDistanceStr[20];
  char lcPctStr[20];
  char lcBattVoltsStr[20];
  int barPixels = -1;

  sprintf( lcDistanceStr, "%ldcm", cm );

  if (distFromBottom < 0) {
    sprintf( lcPctStr, "+%ld!!", (distFromBottom*-1) );
  } else {
    long fillFactor = (distFromBottom * 1000) / TANK_HEIGHT_CM;
    formatDecimals( lcPctStr, fillFactor, 10, "%" );

    barPixels = ( DISPLAY_WIDTH * fillFactor ) / 1000;
  }

  long batteryVoltage = readVcc();
  long batteryVoltage1dec = batteryVoltage / 100; // Just 1 decimal
  formatDecimals( lcBattVoltsStr, batteryVoltage1dec, 10, "V" );

  #ifdef SERIAL_OUTPUT_ENABLED
  Serial.print(lcPctStr);
  Serial.print(" - ");
  Serial.print(lcDistanceStr);
  Serial.print(" - ");
  Serial.print(lcBattVoltsStr);
  Serial.println();
  #endif

  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_fub30r);
    drawStrCentered( u8g, lcPctStr, 32 );

    if (barPixels != -1) {
      u8g.drawBox( DISPLAY_MINX+1, 38, barPixels-1, 8 );
      u8g.drawLine( DISPLAY_MAXX, 38, DISPLAY_MAXX, 38+8 );
    }

    u8g.setFont(u8g_font_fub11r);
    drawStrLeft( u8g, lcDistanceStr, DISPLAY_MAXY );

    if ( batteryVoltage <= LOWBATT_PANIC_MODE_THRESHOLD_MV ) {
      if ( currentBlinkON )
        drawStrRight( u8g, lcBattVoltsStr, DISPLAY_MAXY );
    } else {
      drawStrRight( u8g, lcBattVoltsStr, DISPLAY_MAXY );
    }

    if ( currentBlinkON ) {
      u8g.drawDisc( (DISPLAY_MAXX-DISPLAY_MINX)/2, 58, 4 );
    }

  } while( u8g.nextPage() );
}

void setup() {
  #ifdef SERIAL_OUTPUT_ENABLED
  Serial.begin(9600);
  #endif

  u8g.setColorIndex(1);
  lastBlink = millis();
  currentBlinkON = true;
}

void loop() {
  ultrasonic.DistanceMeasure();
  long distance = ultrasonic.microsecondsToCentimeters();

  unsigned long blinkElapsed = millis() - lastBlink;

  if (currentBlinkON) {
    if (blinkElapsed >= BLINK_ON_TIME) {
      currentBlinkON = !currentBlinkON;
      lastBlink = millis();
    }
  } else {
    if (blinkElapsed >= BLINK_OFF_TIME) {
      currentBlinkON = !currentBlinkON;
      lastBlink = millis();
    }
  }

  updateUI(distance);
  delay(10);
}
