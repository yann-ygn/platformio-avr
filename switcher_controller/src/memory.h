#include <Arduino.h>

#include "eeprom.h"

#ifndef MEMORY_H
#define MEMORY_H

/**
 * @brief Interface between the hardware and the eeprom
 */
class Memory
{
    private:
        Eeprom eeprom0;

        const uint8_t c_initialSetupStateAddress = 0;
        const uint8_t c_currentPresetBankAddress = 1;
        const uint8_t c_currentPresetAddress = 2;
        const uint8_t c_presetSaveStartAddress = 128;
        const uint16_t c_presetBankSaveSize = 256;
        const uint8_t c_presetSaveSize = 64;

    public:
        Memory(uint8_t pin) : eeprom0(pin) {}

        void memorySetup();
        void memoryInitialization();
        void memoryReset();
        void memoryTest();

        uint8_t readInitialSetupState();
        void writeInitialSetupState(uint8_t state);

        uint8_t readCurrentPresetBank();
        void writeCurrentPresetBank(uint8_t bank);

        uint8_t readCurrentPreset();
        void writeCurrentPreset(uint8_t preset);

        void writePreset(uint8_t bank, uint8_t* preset, uint8_t* loopsid, uint8_t* loopsstate, uint8_t* loopsorder, uint8_t loopscount);
        void readPreset(uint8_t bank, uint8_t* preset, uint8_t* loopsid, uint8_t* loopsstate, uint8_t* loopsorder, uint8_t loopscount);
};

#endif