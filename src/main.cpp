#include "Arduino.h"
#include "U8glib.h"
#include "3rdParty/JC_Button/JC_Button.h"
#include "config.h"
#include "utils/utils.h"
#include "utils/eepromcfg.h"
#include "ui/uimgr.h"

// Globals
DISPLAY_CLASS u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0); // I2C / TWI
Button btnUp(BUTTON_UP_PIN, BUTTON_DEBOUNCE_MS, BUTTON_INTERNAL_PULLUP, BUTTON_INVERT);
Button btnDown(BUTTON_DOWN_PIN, BUTTON_DEBOUNCE_MS, BUTTON_INTERNAL_PULLUP, BUTTON_INVERT);
ui::UIMgr uiMgr;
EEPROMCfg cfg;

void setup()
{
#ifdef SERIAL_OUTPUT_ENABLED
    Serial.begin(9600);
    Serial.println("Jelou!");
#endif

    pinMode(PING_TRIGGER_PIN, OUTPUT);
    pinMode(PING_ECHO_PIN, INPUT);

    pinMode(BUTTON_UP_PIN, INPUT);
    pinMode(BUTTON_DOWN_PIN, INPUT);

    u8g.setColorIndex(1);
    btnUp.begin();
    btnDown.begin();

    uiMgr.setup(&cfg, &u8g, &btnUp, &btnDown);
}

void loop()
{
    uiMgr.loop();
    delay(LOOP_SLEEP_MS);
}
