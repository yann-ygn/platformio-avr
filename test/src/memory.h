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

        const uint8_t c_initialSetupStateAddress = 20;
        const uint8_t c_midiChannelAddress = 21;
        const uint8_t c_bypassStateAddress = 22;
        const uint8_t c_presetModeAddress = 23;
        const uint8_t c_currentPresetAddress = 24;
        const uint8_t c_tapStateAddress = 25;
        const uint8_t c_divStateAddress = 26;
        const uint8_t c_divValueAddress = 27;
        const uint16_t c_intervalAddress = 28;
        const uint16_t c_divIntervalAddress = 30;
    

    public:
        Memory(uint8_t pin) : eeprom0(pin) {}

        void memorySetup();
        void memoryInitialization();
        void memoryReset();
        
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