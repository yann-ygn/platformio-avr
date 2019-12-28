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

        const uint8_t c_initialSetupStateAddress = 0;
        const uint8_t c_bypassStateAddress = 1;
        const uint8_t c_presetModeAddress = 2;
        const uint8_t c_currentPresetAddress = 3;
        const uint8_t c_tapStateAddress = 4;
        const uint8_t c_intervalAddress = 5;
        const uint8_t c_divStateAddress = 7;
        const uint8_t c_divValueAddress = 8;
        const uint8_t c_divIntervalAddress = 9;
    

    public:
        Memory() : eeprom0(23) {}

        void memorySetup();
        
        uint8_t readInitialSetupState();
        void writeInitialSetupState(uint8_t state);

        uint8_t readBypassState();
        void writeBypassState(uint8_t state);

        uint8_t readPresetMode();
        void writePresetMode(uint8_t mode);

        uint8_t readCurrentPreset();
        void writeCurrentPreset(uint8_t preset);

        uint8_t readTapState();
        void writeTapState(uint8_t state);

        int readIntervalValue();
        void writeIntervalValue(int value);

        uint8_t readDivState();
        void writeDivState(uint8_t state);

        uint8_t readDivValue();
        void writeDivValue(byte value);

        int readDivIntervalValue();
        void writeDivIntervalValue(int value);
};

#endif