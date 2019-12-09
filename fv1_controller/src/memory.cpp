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

uint8_t Memory::readTapState()
{
    return eeprom0.readByte(c_tapStateAddress);
}

void Memory::writeTapState(uint8_t state)
{
    eeprom0.writeByte(c_tapStateAddress, state);
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