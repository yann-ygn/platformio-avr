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
        const uint8_t c_intervalAddress = 28;
        const uint8_t c_divIntervalAddress = 30;
        const uint8_t c_preset0Address = 65;
        const uint8_t c_preset1Address = 80;
        const uint8_t c_preset2Address = 95;
        const uint8_t c_preset3Address = 110;
        const uint8_t c_preset4Address = 130;
        const uint8_t c_preset5Address = 145;
        const uint8_t c_preset6Address = 160;
        const uint8_t c_preset7Address = 175;

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

        /**
         * data[16]
         * data[0] : m_currentProgram
         * data[1] : m_tapState
         * data[2] : m_divState
         * data[3] : m_divValue
         * data[4-5] : m_interval
         * data[6-7] : m_divInterval
         * data[8-9] : pot0Value
         * data[10-11] : pot1Value
         * data[12-13] : pot2Value
         * data[14-15] : pot3Value
         */

        /**
         * @brief 
         * 
         * @param preset 
         * @param data 
         */
        void readPreset(uint8_t preset, uint8_t * program, uint8_t * tap, uint8_t * div, uint8_t * divvalue, uint16_t * interval, 
                        uint16_t * divinterval, uint16_t * pot0, uint16_t * pot1, uint16_t * pot2, uint16_t * pot3);
        void writePreset(uint8_t preset, uint8_t * program, uint8_t * tap, uint8_t * div, uint8_t * divvalue, uint16_t * interval, 
                        uint16_t * divinterval, uint16_t * pot0, uint16_t * pot1, uint16_t * pot2, uint16_t * pot3);
};

#endif