#pragma once

#include "Arduino.h"
#include "U8glib.h"
#include "../config.h"
#include "../3rdParty/JC_Button/JC_Button.h"

namespace ui
{

    class UIMgr;

    class UIState
    {
    public:
        // State constants
        const static int MEASURE = 0;
        const static int SETTINGS = 1;

    protected:
        UIMgr *ui;
        DISPLAY_CLASS *display;
        Button *btnUp;
        Button *btnDown;
        bool active;
        unsigned long lastBlink;
        bool currentBlinkON;
        bool waitingButtonRelease;

    public:
        UIState(UIMgr *pUI);

        virtual void setup();
        virtual void onEnter();
        virtual void onExit();
        virtual void calcBlink();

        virtual void beforePaint();
        virtual void paint();
        virtual bool afterPaint();
    };

} // namespace ui
