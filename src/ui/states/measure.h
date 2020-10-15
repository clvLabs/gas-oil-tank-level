#pragma once

#include "Arduino.h"
#include <NewPing.h>
#include "U8glib.h"
#include "../../config.h"
#include "../../utils/u8gutils.h"
#include "../../utils/battery.h"
#include "../../utils/utils.h"
#include "../uistate.h"

namespace ui
{

    class Measure : public UIState
    {
        NewPing *pingSensor;

        long fillFactor;
        char distanceStr[20];
        char pctStr[20];
        char batteryStr[20];
        bool batteryWarning;

    public:
        Measure(UIMgr *pUI);

        void setup();
        void beforePaint();
        void paint();
        bool afterPaint();
        void calcDistance();
    };

} // namespace ui
