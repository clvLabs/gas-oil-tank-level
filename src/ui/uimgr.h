#pragma once

#include "../config.h"
#include "../utils/eepromcfg.h"
#include "./uistate.h"

class EEPROMCfg;

namespace ui
{

    static const int MAX_STATES = 10;

    class UIMgr
    {
    public:
        EEPROMCfg *cfg;
        DISPLAY_CLASS *display;
        Button *btnUp;
        Button *btnDown;
        UIState *states[MAX_STATES];
        int numstates;
        int currstate;

    public:
        UIMgr();

        void setup(EEPROMCfg *pCfg, DISPLAY_CLASS *pDisplay, Button *pBtnUp, Button *pBtnDown);
        void loop();

        void setCurrState(int state);
    };

} // namespace ui
