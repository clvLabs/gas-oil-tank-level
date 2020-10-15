#include "../../utils/eepromcfg.h"
#include "../uimgr.h"
#include "./measurecm.h"

namespace ui
{

    MeasureCm::MeasureCm(UIMgr *pUI)
        : UIState(pUI)
    {
    };

    void MeasureCm::setup()
    {
        UIState::setup();
        pingSensor = new NewPing(PING_TRIGGER_PIN, PING_ECHO_PIN, PING_MAX_DISTANCE);
    }

    void MeasureCm::beforePaint()
    {
        UIState::beforePaint();

        calcData();
    }

    void MeasureCm::paint()
    {
        UIState::paint();

        display->setFont(u8g_font_fub30r);
        drawStrCentered(*display, distanceStr, DISPLAY_MAXY);
    }

    bool MeasureCm::afterPaint()
    {
        if (!UIState::afterPaint())
            return false;

        if (btnUp->wasReleased() || btnDown->wasReleased())
        {
            ui->setCurrState(UIState::MEASUREPCT);
            return false;
        }

        return true;
    }

    void MeasureCm::calcData()
    {
        unsigned long cm = pingSensor->ping_cm();
        sprintf(distanceStr, "%ld", cm);
    }

} // namespace ui
