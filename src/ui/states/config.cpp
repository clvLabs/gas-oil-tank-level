#include "../../utils/eepromcfg.h"
#include "../uimgr.h"
#include "./config.h"

namespace ui
{

    Config::Config(UIMgr *pUI)
        : UIState(pUI), currentField(0)
    {
    }

    void Config::setup()
    {
        UIState::setup();
    }

    void Config::onEnter()
    {
        UIState::onEnter();
        currentField = 0;
    }

    void Config::beforePaint()
    {
        UIState::beforePaint();

        if (currentField == 0)
        {
            updateValue(&ui->cfg->data.minLevelCm, ui->cfg->data.maxLevelCm + 1, PING_MAX_DISTANCE);
            sprintf(valueStr, "%dcm", ui->cfg->data.minLevelCm);
        }
        else if (currentField == 1)
        {
            updateValue(&ui->cfg->data.maxLevelCm, 1, ui->cfg->data.minLevelCm - 1);
            sprintf(valueStr, "%dcm", ui->cfg->data.maxLevelCm);
        }
        else
            sprintf(valueStr, "???");
    }

    void Config::paint()
    {
        UIState::paint();

        display->setFont(u8g_font_fub20r);
        if (currentField == 0)
            drawStrCentered(*display, "[MAX]", 20); // Not inverted! (really, just 4 the user)
        else if (currentField == 1)
            drawStrCentered(*display, "[MIN]", 20); // Not inverted! (really, just 4 the user)
        else
            drawStrCentered(*display, "[???]", 20);

        drawStrCentered(*display, valueStr, 50);
    }

    bool Config::afterPaint()
    {
        if (!UIState::afterPaint())
            return false;

        if (btnUp->pressedFor(BUTTON_HOLD_TIME) || btnDown->pressedFor(BUTTON_HOLD_TIME))
        {
            switch (currentField)
            {
            case 0:
                currentField++;
                waitingButtonRelease = true;
                return false;
                break;

            case 1:
                ui->cfg->write();
                ui->setCurrState(UIState::MEASURE);
                return false;
                break;

            default:
                break;
            }
        }

        return true;
    }

    void Config::updateValue(unsigned int *pValue, unsigned int pMin, unsigned int pMax)
    {
        if (waitingButtonRelease)
            return;

        if (btnDown->wasReleased())
        {
            if (*pValue > pMin)
                (*pValue)--;
        }
        else if (btnUp->wasReleased())
        {
            if (*pValue < pMax)
                (*pValue)++;
        }
    }

} // namespace ui
