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
        const uint8_t c_midiChannelAddress = 1;
        const uint8_t c_bypassStateAddress = 2;
        const uint8_t c_presetModeAddress = 3;
        const uint8_t c_currentPresetAddress = 4;
        const uint8_t c_tapStateAddress = 5;
        const uint8_t c_divStateAddress = 6;
        const uint8_t c_divValueAddress = 7;
        const uint16_t c_intervalAddress = 8;
        const uint16_t c_divIntervalAddress = 10;
    

    public:
        Memory() : eeprom0(2) {}

        void memorySetup();
        void memoryInitialization();
        
        uint8_t readInitialSetupState();
        void writeInitialSetupState(uint8_t state);

        uint8_t readMidiChannel();
        void writeMidiChannel(uint8_t channel);

        uint8_t readBypassState();
        void writeBypassState(uint8_t state);

        uint8_t readPresetMode();
        void writePresetMode(uint8_t mode);

        uint8_t readCurrentPreset();
        void writeCurrentPreset(uint8_t preset);

        uint8_t readTapState();
        void writeTapState(uint8_t state);

        uint16_t readIntervalValue();
        void writeIntervalValue(uint16_t value);

        uint8_t readDivState();
        void writeDivState(uint8_t state);

        uint8_t readDivValue();
        void writeDivValue(byte value);

        uint16_t readDivIntervalValue();
        void writeDivIntervalValue(uint16_t value);
};

#endif