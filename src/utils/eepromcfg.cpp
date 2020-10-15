#include "config.h"
#include "eepromcfg.h"
#include "EEPROM.h"

EEPROMCfg::EEPROMCfg()
{
    read();
}

void EEPROMCfg::read()
{
    uint8_t *lCfgPtr = (uint8_t *)&originalData;

    for (uint8_t liAddress = 0; liAddress < sizeof(struct _EEPROM_Config); liAddress++)
        lCfgPtr[liAddress] = EEPROM.read(liAddress);

    // If program signature is not found, initialize EEPROM
    if (originalData.miProgramSignature != PROGRAM_EEPROM_SIGNATURE)
        init();

    memcpy((void *)&data, (void *)&originalData, sizeof(struct _EEPROM_Config));
}

void EEPROMCfg::write()
{
    // Skip if not changed!
    if (!memcmp((void *)&originalData, (void *)&data, sizeof(struct _EEPROM_Config)))
        return;

    uint8_t *lCfgPtr = (uint8_t *)&data;

    for (uint8_t liAddress = 0; liAddress < sizeof(struct _EEPROM_Config); liAddress++)
        EEPROM.write(liAddress, lCfgPtr[liAddress]);

    memcpy((void *)&originalData, (void *)&data, sizeof(struct _EEPROM_Config));
}

void EEPROMCfg::init()
{
    // Initialize original data
    memset((void *)&originalData, 0, sizeof(struct _EEPROM_Config));

    // Set default configuration values
    data.miProgramSignature = PROGRAM_EEPROM_SIGNATURE;
    data.minLevelCm = MIN_LEVEL_CM_DEFAULT;
    data.maxLevelCm = MAX_LEVEL_CM_DEFAULT;

    // Write new values to EEPROM
    write();
}

unsigned int EEPROMCfg::getTankHeightCm()
{
    return data.minLevelCm - data.maxLevelCm;
}
