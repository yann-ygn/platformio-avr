#define DEBUG 1

#include <Arduino.h>

#include "memory.h"

void Memory::memorySetup()
{
    eeprom0.eepromSetup();

    uint8_t statusRegister = eeprom0.readStatusRegister();

    #ifdef DEBUG
        Serial.print("Status register : ");
        Serial.println(statusRegister);
    #endif

    if ((statusRegister & B10000000) == 1 || // SRWD is set
    (statusRegister & B00001000) == 1 || // BP1 is set
    (statusRegister & B00000100) == 1)   // BP0 is set
    {
        #ifdef DEBUG
            Serial.println("Doing status register reinitialization");
        #endif

        eeprom0.writeStatusRegister(); // Reset the status register
    }

    if (readInitialSetupState() != 1) // First startup, need to initialize
    {
        memoryInitialization();
    }
}

void Memory::memoryInitialization()
{
    writeInitialSetupState(1);
}

void Memory::memoryReset()
{

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

}

uint16_t writePreset(uint8_t bank, uint8_t preset, uint8_t* loop, uint8_t* loopstate, uint8_t loopcount)
{
    
}

void Memory::memoryTest()
{
    eeprom0.testInt8();
}