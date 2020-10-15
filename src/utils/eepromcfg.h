#pragma once

#include "Arduino.h"

// EEPROM stored configuration
struct _EEPROM_Config
{
    // Program EEPROM signature
    uint16_t miProgramSignature;

    unsigned int minLevelCm;
    unsigned int maxLevelCm;
};

class EEPROMCfg
{
public:
    struct _EEPROM_Config data;

private:
    struct _EEPROM_Config originalData;

public:
    EEPROMCfg();

    void init();
    void read();
    void write();

    unsigned int getTankHeightCm();
};
