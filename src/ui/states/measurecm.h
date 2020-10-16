#pragma once

#include <NewPing.h>
#include "../uistate.h"

namespace ui
{

    class MeasureCm : public UIState
    {
        NewPing *pingSensor;

        char distanceStr[20];

    public:
        MeasureCm(UIMgr *pUI);

        void setup();
        void beforePaint();
        void paint();
        bool afterPaint();
        void calcData();
    };

} // namespace ui
