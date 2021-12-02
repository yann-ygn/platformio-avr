#include <Arduino.h>

#include "eeprom.h"

#ifndef MEMORY_H
#define MEMORY_H

/**
 * @brief Manages
 */
class Memory
{
    private:
        Eeprom eeprom0;

        const uint8_t c_initialSetupStateAddress = 0;
        const uint8_t c_presetSaveStartAddress = 128;
        const uint8_t c_presetPresetSaveSize = 16;
        const uint8_t c_presetBankSaveSize = 64;

    public:
        Memory(uint8_t pin) : eeprom0(pin) {}

        void memorySetup();
        void memoryInitialization();
        void memoryReset();
        void memoryTest();

        uint8_t readInitialSetupState();
        void writeInitialSetupState(uint8_t state);

        void writePreset(uint8_t bank, uint8_t preset, uint8_t* loop, uint8_t* loopstate, uint8_t loopcount);
        void readPreset(uint8_t bank, uint8_t preset, uint8_t* loop, uint8_t* loopstate, uint8_t loopcount);
};

#endif