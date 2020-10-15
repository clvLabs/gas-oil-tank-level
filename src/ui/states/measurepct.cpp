#include "../../utils/eepromcfg.h"
#include "../uimgr.h"
#include "./measurepct.h"

namespace ui
{

    MeasurePct::MeasurePct(UIMgr *pUI)
        : UIState(pUI)
    {
        fillFactor = -1;
        batteryWarning = false;
    };

    void MeasurePct::setup()
    {
        UIState::setup();
        pingSensor = new NewPing(PING_TRIGGER_PIN, PING_ECHO_PIN, PING_MAX_DISTANCE);
    }

    void MeasurePct::beforePaint()
    {
        UIState::beforePaint();

        calcData();

#ifdef SERIAL_OUTPUT_ENABLED
        Serial.print(pctStr);
        Serial.print(" - ");
        Serial.print(distanceStr);
        Serial.print(" - ");
        Serial.print(batteryStr);
        Serial.println();
#endif
    }

    void MeasurePct::paint()
    {
        UIState::paint();

        display->setFont(u8g_font_fub30r);
        drawStrCentered(*display, pctStr, 32);

        if (fillFactor != -1)
        {
            int barPixels = (DISPLAY_WIDTH * fillFactor) / 100;
            display->drawBox(DISPLAY_MINX + 1, 38, barPixels - 1, 8);
            display->drawLine(DISPLAY_MAXX, 38, DISPLAY_MAXX, 38 + 8);
        }

        display->setFont(u8g_font_fub11r);
        drawStrLeft(*display, distanceStr, DISPLAY_MAXY);

        if (batteryWarning)
        {
            if (currentBlinkON)
                drawStrRight(*display, batteryStr, DISPLAY_MAXY);
        }
        else
        {
            drawStrRight(*display, batteryStr, DISPLAY_MAXY);
        }
    }

    bool MeasurePct::afterPaint()
    {
        if (!UIState::afterPaint())
            return false;

        if (btnUp->pressedFor(BUTTON_HOLD_TIME) && btnDown->pressedFor(BUTTON_HOLD_TIME))
        {
            ui->setCurrState(UIState::SETTINGS);
            return false;
        }
        else if (btnUp->wasReleased() || btnDown->wasReleased())
        {
            ui->setCurrState(UIState::MEASURECM);
            return false;
        }

        return true;
    }

    void MeasurePct::calcData()
    {
        unsigned long cm = pingSensor->ping_cm();
        long distFromBottom = ui->cfg->data.minLevelCm - cm;

        sprintf(distanceStr, "%ldcm", cm);

        if (distFromBottom < 0)
        {
            fillFactor = -1;
            sprintf(pctStr, "+%ld!!", (distFromBottom * -1));
        }
        else
        {
            fillFactor = ((distFromBottom * 100) + 50) / ui->cfg->getTankHeightCm();
            sprintf(pctStr, "%ld%%", fillFactor);
        }

        getBatteryVoltsStr(batteryStr);
        batteryWarning = (getBatteryVolts() <= LOWBATT_PANIC_MODE_THRESHOLD_MV);
    }

} // namespace ui
