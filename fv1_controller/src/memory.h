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

        const uint16_t c_initialSetupStateAddress = 0;
        const uint16_t c_midiChannelAddress = 1;
        const uint16_t c_bypassStateAddress = 2;
        const uint16_t c_presetModeAddress = 3;
        const uint16_t c_currentPresetAddress = 4;
        const uint16_t c_currentProgramAddress = 5;
        const uint16_t c_tapStateAddress = 6;
        const uint16_t c_divStateAddress = 7;
        const uint16_t c_divValueAddress = 8;
        const uint16_t c_intervalAddress = 9;
        const uint16_t c_divIntervalAddress = 11;
        const uint16_t c_program0ExpreSettingAddress = 13;
        const uint16_t c_program1ExpreSettingAddress = 14;
        const uint16_t c_program2ExpreSettingAddress = 15;
        const uint16_t c_program3ExpreSettingAddress = 16;
        const uint16_t c_program4ExpreSettingAddress = 17;
        const uint16_t c_program5ExpreSettingAddress = 18;
        const uint16_t c_program6ExpreSettingAddress = 19;
        const uint16_t c_program7ExpreSettingAddress = 10;
        const uint16_t c_preset0Address = 65;
        const uint16_t c_preset1Address = 80;
        const uint16_t c_preset2Address = 95;
        const uint16_t c_preset3Address = 110;
        const uint16_t c_preset4Address = 130;
        const uint16_t c_preset5Address = 145;
        const uint16_t c_preset6Address = 160;
        const uint16_t c_preset7Address = 175;

    public:
        Memory(uint8_t pin) : eeprom0(pin) {}

        void memorySetup();
        void memoryInitialization();
        void memoryReset();
        void memoryTest();
        
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

        uint8_t readCurrentProgram();
        void writeCurrentProgram(uint8_t program);

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

        uint8_t readProgramExprSetting(uint8_t program);
        void writeProgramExprSetting(uint8_t program, uint8_t setting);

        /**
         * data[16]
         * data[0] : m_currentProgram
         * data[1] : m_tapState
         * data[2] : m_divState
         * data[3] : m_divValue
         * data[4-5] : m_interval
         * data[6-7] : m_divInterval
         * data[8] : pot0Value
         * data[9] : pot1Value
         * data[10] : pot2Value
         * data[11] : pot3Value
         * data[12] : m_programExprSetting
         */

        /**
         * @brief 
         * 
         * @param preset 
         * @param data 
         */
        void readPreset(uint8_t preset, uint8_t * program, uint8_t * tap, uint8_t * div, uint8_t * divvalue, uint16_t * interval, 
                        uint16_t * divinterval, uint8_t * pot0, uint8_t * pot1, uint8_t * pot2, uint8_t * pot3, uint8_t * expr);
        void writePreset(uint8_t preset, uint8_t program, uint8_t tap, uint8_t div, uint8_t divvalue, uint16_t interval, 
                        uint16_t divinterval, uint8_t pot0, uint8_t pot1, uint8_t pot2, uint8_t pot3, uint8_t expr);
};

#endif