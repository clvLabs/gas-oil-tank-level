#pragma once

#include "Arduino.h"
#include "config.h"


void formatDecimals(char* buf, long val, int decimals, const char* suffix) {
    int intPart = val / decimals;
    int decimalPart = val % decimals;
    sprintf( buf, "%d.%d%s", intPart, decimalPart, suffix );
}
