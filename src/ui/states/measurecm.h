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
