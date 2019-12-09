#include <Arduino.h>

#include "M95256.h"

#ifndef MEMORY_H
#define MEMORY_H

/**
 * @brief Manages 
 */
class Memory
{
    private:
        M95256 eeprom0;

        const uint8_t c_bypassStateAddress = 0;
        const uint8_t c_presetModeAddress = 1;
        const uint8_t c_currentPresetAddress = 2;
        const uint8_t c_tapStateAddress = 3;
    

    public:
        Memory() : eeprom0(20) {}

        void memorySetup();

        uint8_t readBypassState();
        void writeBypassState(uint8_t state);

        uint8_t readTapState();
        void writeTapState(uint8_t state);

        uint8_t readPresetMode();
        void writePresetMode(uint8_t mode);

        uint8_t readCurrentPreset();
        void writeCurrentPreset(uint8_t preset);
};

#endif