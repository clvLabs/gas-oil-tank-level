#include "Arduino.h"
#include "readvcc.h"
#include "utils.h"

long getBatteryVolts()
{
    return readVcc();
}

void getBatteryVoltsStr(char *buf)
{
    long batteryVoltage = readVcc();
    long batteryVoltage1dec = batteryVoltage / 100; // Just 1 decimal
    formatDecimals(buf, batteryVoltage1dec, 10, "V");
}
