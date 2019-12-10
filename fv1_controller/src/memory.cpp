#include <Arduino.h>

#include "memory.h"

void Memory::memorySetup()
{
    eeprom0.setup();
}

uint8_t Memory::readBypassState()
{
    return eeprom0.readByte(c_bypassStateAddress);
}

void Memory::writeBypassState(uint8_t state)
{
    eeprom0.writeByte(c_bypassStateAddress, state);
}

uint8_t Memory::readPresetMode()
{
    return eeprom0.readByte(c_presetModeAddress);
}

void Memory::writePresetMode(uint8_t mode)
{
    eeprom0.writeByte(c_presetModeAddress, mode);
}

uint8_t Memory::readCurrentPreset()
{
    return eeprom0.readByte(c_currentPresetAddress);
}

void Memory::writeCurrentPreset(uint8_t preset)
{
    eeprom0.writeByte(c_currentPresetAddress, preset);
}

uint8_t Memory::readCurrentProgram()
{
    return eeprom0.readByte(c_currentProgramAddress);
}

void Memory::writeCurrentProgram(uint8_t program)
{
    eeprom0.writeByte(c_currentProgramAddress, program);
}

uint8_t Memory::readTapState()
{
    return eeprom0.readByte(c_tapStateAddress);
}

void Memory::writeTapState(uint8_t state)
{
    eeprom0.writeByte(c_tapStateAddress, state);
}

uint8_t Memory::readDivValue()
{
    return eeprom0.readByte(c_divValueAddress);
}

void Memory::writeDivValue(uint8_t value)
{
    eeprom0.writeByte(c_divValueAddress, value);
}