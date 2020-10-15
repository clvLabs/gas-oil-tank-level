#include "./uimgr.h"
#include "./uistate.h"

namespace ui
{

    UIState::UIState(UIMgr *pUI)
        : ui(pUI)
    {
        display = ui->display;
        btnUp = ui->btnUp;
        btnDown = ui->btnDown;

        lastBlink = millis();
        currentBlinkON = true;
        waitingButtonRelease = true;
    };

    void UIState::setup()
    {
    }

    void UIState::onEnter()
    {
        active = true;
        waitingButtonRelease = true;
    }

    void UIState::onExit()
    {
        active = false;
        waitingButtonRelease = false;
    }

    void UIState::calcBlink()
    {
        unsigned long blinkElapsed = millis() - lastBlink;

        if (currentBlinkON)
        {
            if (blinkElapsed >= BLINK_ON_TIME)
            {
                currentBlinkON = !currentBlinkON;
                lastBlink = millis();
            }
        }
        else
        {
            if (blinkElapsed >= BLINK_OFF_TIME)
            {
                currentBlinkON = !currentBlinkON;
                lastBlink = millis();
            }
        }
    }

    void UIState::beforePaint()
    {
        calcBlink();
    }

    void UIState::paint()
    {
        if (currentBlinkON)
        {
            display->drawDisc(DISPLAY_MAXX - 4, 4, 4);
        }
    }

    bool UIState::afterPaint()
    {
        if (waitingButtonRelease)
        {
            // Wait until user releases buttons pressed to enter here!
            if (btnUp->isPressed() || btnDown->isPressed())
            {
                return false;
            }
            else
            {
                waitingButtonRelease = false;
                return false;
            }
        }

        return true;
    }

} // namespace ui
