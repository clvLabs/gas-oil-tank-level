#pragma once

#include "../uistate.h"

namespace ui
{

    class Settings : public UIState
    {
        int currentField;
        char valueStr[20];

    public:
        Settings(UIMgr *pUI);

        void setup();
        void loop();
        void onEnter();
        void beforePaint();
        void paint();
        bool afterPaint();

    private:
        void updateValue(unsigned int *pValue, unsigned int pMin, unsigned int pMax);
    };

} // namespace ui
