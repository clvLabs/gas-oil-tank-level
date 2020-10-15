#include "./uimgr.h"

#include "../utils/u8gutils.h"
#include "../utils/battery.h"
#include "../utils/utils.h"
#include "../utils/eepromcfg.h"
#include "./states/measure.h"
#include "./states/config.h"

namespace ui
{

    UIMgr::UIMgr(){};

    void UIMgr::setup(EEPROMCfg *pCfg, DISPLAY_CLASS *pDisplay, Button *pBtnUp, Button *pBtnDown)
    {
        cfg = pCfg;
        display = pDisplay;
        btnUp = pBtnUp;
        btnDown = pBtnDown;
        numstates = 0;
        currstate = -1;

        states[UIState::MEASURE] = new Measure(this);
        numstates++;
        states[UIState::CONFIG] = new Config(this);
        numstates++;

        setCurrState(UIState::MEASURE);

        for (int i = 0; i < numstates; i++)
        {
            states[i]->setup();
        }
    }

    void UIMgr::loop()
    {
        btnUp->read();
        btnDown->read();

        states[currstate]->beforePaint();

        display->firstPage();
        do
        {
            states[currstate]->paint();
        } while (display->nextPage());

        states[currstate]->afterPaint();
    }

    void UIMgr::setCurrState(int state)
    {
        if (currstate != -1)
            states[currstate]->onExit();

        currstate = state;
        states[currstate]->onEnter();
    }

} // namespace ui
