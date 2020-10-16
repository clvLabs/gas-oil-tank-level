#include "Arduino.h"
#include "utils.h"

void formatDecimals(char *buf, long val, int decimals, const char *suffix)
{
    int intPart = val / decimals;
    int decimalPart = val % decimals;
    sprintf(buf, "%d.%d%s", intPart, decimalPart, suffix);
}
