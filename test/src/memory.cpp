#define DEBUG 1

#include <Arduino.h>

#include "memory.h"

void Memory::memorySetup()
{
    eeprom0.eepromSetup();

    if (readInitialSetupState() != 1) // First startup, need to initialize
    {
        memoryInitialization();
    }
}

void Memory::memoryInitialization()
{
    #ifdef DEBUG
        Serial.println("Doing memory initialization");
    #endif

    writeMidiChannel(0);
    writeBypassState(0);
    writePresetMode(0);
    writeCurrentPreset(0);
    writeTapState(0);
    writeDivState(0);
    writeDivValue(1);
    writeDivIntervalValue(0);
    writeIntervalValue(0);

    writeInitialSetupState(1); // Initialization done
}

void Memory::memoryReset()
{
    #ifdef DEBUG
        Serial.println(eeprom0.test());
    #endif/**
    writeInitialSetupState(0);
    writeMidiChannel(0);
    writeBypassState(0);
    writePresetMode(0);
    writeCurrentPreset(0);
    writeTapState(0);
    writeDivState(0);
    writeDivValue(0);
    writeIntervalValue(0);
    writeDivIntervalValue(0);**/
}

uint8_t Memory::readInitialSetupState()
{
    uint8_t value = eeprom0.readInt8(c_initialSetupStateAddress);

    #ifdef DEBUG
        Serial.print("Reading initial state : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeInitialSetupState(uint8_t state)
{
    #ifdef DEBUG
        Serial.print("Writing initial state : ");
        Serial.println(state);
    #endif

    eeprom0.writeInt8(c_initialSetupStateAddress, state);
}

uint8_t Memory::readMidiChannel()
{
    uint8_t value = eeprom0.readInt8(c_midiChannelAddress);

    #ifdef DEBUG
        Serial.print("Reading midi channel : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeMidiChannel(uint8_t channel)
{
    #ifdef DEBUG
        Serial.print("Writing midi channel : ");
        Serial.println(channel);
    #endif

    eeprom0.writeInt8(c_midiChannelAddress, channel);
}

uint8_t Memory::readBypassState()
{
    uint8_t value = eeprom0.readInt8(c_bypassStateAddress);

    #ifdef DEBUG
        Serial.print("Reading bypass state : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeBypassState(uint8_t state)
{
    #ifdef DEBUG
        Serial.print("Writing bypass state : ");
        Serial.println(state);
    #endif

    eeprom0.writeInt8(c_bypassStateAddress, state);
}

uint8_t Memory::readPresetMode()
{
    uint8_t value = eeprom0.readInt8(c_presetModeAddress);

    #ifdef DEBUG
        Serial.print("Reading preset mode : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writePresetMode(uint8_t mode)
{
    #ifdef DEBUG
        Serial.print("Writing preset mode : ");
        Serial.println(mode);
    #endif

    eeprom0.writeInt8(c_presetModeAddress, mode);
}

uint8_t Memory::readCurrentPreset()
{
    uint8_t value = eeprom0.readInt8(c_currentPresetAddress);

    #ifdef DEBUG
        Serial.print("Reading current preset : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeCurrentPreset(uint8_t preset)
{
    #ifdef DEBUG
        Serial.print("Writing current preset : ");
        Serial.println(preset);
    #endif

    eeprom0.writeInt8(c_currentPresetAddress, preset);
}

uint8_t Memory::readTapState()
{
    uint8_t value = eeprom0.readInt8(c_tapStateAddress);

    #ifdef DEBUG
        Serial.print("Reading tap state : ");
        Serial.println(value);
    #endif

    return value;
}


void Memory::writeTapState(uint8_t state)
{
    #ifdef DEBUG
        Serial.print("Writing tap state : ");
        Serial.println(state);
    #endif

    eeprom0.writeInt8(c_tapStateAddress, state);
}

uint16_t Memory::readIntervalValue()
{
    int value = eeprom0.readInt16(c_intervalAddress);

    #ifdef DEBUG
        Serial.print("Reading interval value : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeIntervalValue(uint16_t value)
{
    #ifdef DEBUG
        Serial.print("Writing interval value : ");
        Serial.println(value);
    #endif

    eeprom0.writeInt16(c_intervalAddress, value);
}

uint8_t Memory::readDivState()
{
    uint8_t value = eeprom0.readInt8(c_divStateAddress);

    #ifdef DEBUG
        Serial.print("Reading division state : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeDivState(uint8_t state)
{
    #ifdef DEBUG
        Serial.print("Writing division state : ");
        Serial.println(state);
    #endif

    eeprom0.writeInt8(c_divStateAddress, state);
}

uint8_t Memory::readDivValue()
{
    uint8_t value = eeprom0.readInt8(c_divValueAddress);

    #ifdef DEBUG
        Serial.print("Reading division value : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeDivValue(uint8_t value)
{
    #ifdef DEBUG
        Serial.print("Writing division value : ");
        Serial.println(value);
    #endif

    eeprom0.writeInt8(c_divValueAddress, value);
}

uint16_t Memory::readDivIntervalValue()
{
    int value = eeprom0.readInt16(c_divIntervalAddress);

    #ifdef DEBUG
        Serial.print("Reading division interval : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeDivIntervalValue(uint16_t value)
{
    #ifdef DEBUG
        Serial.print("Writing division interval : ");
        Serial.println(value);
    #endif

    eeprom0.writeInt16(c_divIntervalAddress, value);
}
