#include <Arduino.h>

#include "memory.h"

void Memory::memorySetup()
{
    eeprom0.setup();
}

byte Memory::readBypassState()
{
    return eeprom0.readByte(c_bypassStateAddress);
}

void Memory::writeBypassState(byte state)
{
    eeprom0.writeByte(c_bypassStateAddress, state);
}
