#include "./states/measurepct.h"
#include "./states/measurecm.h"
#include "./states/settings.h"
#include "./uimgr.h"

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

        states[UIState::MEASUREPCT] = new MeasurePct(this);
        numstates++;
        states[UIState::MEASURECM] = new MeasureCm(this);
        numstates++;
        states[UIState::SETTINGS] = new Settings(this);
        numstates++;

        setCurrState(UIState::MEASUREPCT);

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
