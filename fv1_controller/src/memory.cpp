#define DEBUG 1

#include <Arduino.h>

#include "memory.h"

void Memory::memorySetup()
{
    eeprom0.setup();
}

uint8_t Memory::readInitialSetupState()
{
    return eeprom0.readByte(c_initialSetupStateAddress);
}

void Memory::writeInitialSetupState(uint8_t state)
{
    eeprom0.writeByte(c_initialSetupStateAddress, state);
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

uint8_t Memory::readTapState()
{
    return eeprom0.readByte(c_tapStateAddress);
}

void Memory::writeTapState(uint8_t state)
{
    eeprom0.writeByte(c_tapStateAddress, state);
}

int Memory::readIntervalValue()
{
    return eeprom0.readInt(c_intervalAddress);
}

void Memory::writeIntervalValue(int value)
{
    eeprom0.writeInt(c_intervalAddress, value);
}

uint8_t Memory::readDivState()
{
    return eeprom0.readByte(c_divStateAddress);
}

void Memory::writeDivState(uint8_t state)
{
    eeprom0.writeByte(c_divStateAddress, state);
}

uint8_t Memory::readDivValue()
{
    return eeprom0.readByte(c_divValueAddress);
}

void Memory::writeDivValue(byte value)
{
    eeprom0.writeByte(c_divValueAddress, value);
}

int Memory::readDivIntervalValue()
{
    return eeprom0.readInt(c_divIntervalAddress);
}

void Memory::writeDivIntervalValue(int value)
{
    eeprom0.writeInt(c_divIntervalAddress, value);
}
