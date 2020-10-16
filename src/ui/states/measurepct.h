#pragma once

#include <NewPing.h>
#include "../uistate.h"

namespace ui
{

    class MeasurePct : public UIState
    {
        NewPing *pingSensor;

        long fillFactor;
        char distanceStr[20];
        char pctStr[20];
        char batteryStr[20];
        bool batteryWarning;

    public:
        MeasurePct(UIMgr *pUI);

        void setup();
        void beforePaint();
        void paint();
        bool afterPaint();
        void calcData();
    };

} // namespace ui
