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
    uint8_t startPreset = 65; // A
    uint8_t maxBanks = 10; // Number of banks
    uint8_t maxPresets = 4; // Number of presets per banks
    uint8_t maxLoops = 6; // Number of loops per preset

    uint8_t loops[maxLoops] = {0};
    uint8_t states[maxLoops] = {0};
    uint8_t* loopsptr = loops;
    uint8_t* statesptr = states;

    for (uint8_t i = 0; i < maxLoops; i++)
    {
        loops[i] = i;
    }

    writeInitialSetupState(1);
    writeCurrentPresetBank(startPreset); // A
    writeCurrentPreset(0);

    for (uint8_t i = startPreset; i < startPreset + maxBanks; i++)
    {
        for (uint8_t j = 0; j < maxPresets; j++)
        {
            writePreset(i, j, loopsptr, statesptr, maxLoops);
        }
    }
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
    eeprom0.writeInt8(c_initialSetupStateAddress, state);

    #ifdef DEBUG
        Serial.print("Writing initial state : ");
        Serial.println(state);
    #endif
}

uint8_t Memory::readCurrentPresetBank()
{
    uint8_t value = eeprom0.readInt8(c_currentPresetBankAddress);

    #ifdef DEBUG
        Serial.print("Reading current preset bank : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeCurrentPresetBank(uint8_t bank)
{
    eeprom0.writeInt8(c_currentPresetBankAddress, bank);

    #ifdef DEBUG
        Serial.print("Writing current preset bank : ");
        Serial.println(bank);
    #endif
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
    eeprom0.writeInt8(c_currentPresetAddress, preset);

    #ifdef DEBUG
        Serial.print("Writing current preset bank : ");
        Serial.println(preset);
    #endif
}

void Memory::writePreset(uint8_t bank, uint8_t preset, uint8_t* loop, uint8_t* loopstate, uint8_t loopcount)
{
    uint16_t startAdress = c_presetSaveStartAddress + ((bank - 65) * c_presetBankSaveSize) + (c_presetSaveSize * preset);

    #ifdef DEBUG
        Serial.println("Writing preset : ");
    #endif

    eeprom0.writeInt8(startAdress, bank);
    startAdress++;

    #ifdef DEBUG
        Serial.print("Preset bank : ");
        Serial.println(bank);
    #endif

    eeprom0.writeInt8(startAdress, preset);
    startAdress++;

    #ifdef DEBUG
        Serial.print("Preset : ");
        Serial.println(preset);
    #endif

    eeprom0.writeArray(startAdress, loop, loopcount);
    startAdress += loopcount;

    eeprom0.writeArray(startAdress, loopstate, loopcount);
    startAdress += loopcount;

    #ifdef DEBUG
        for (uint8_t i = 0; i < loopcount; i++)
        {
            Serial.print("Loop ");
            Serial.print(loop[i]);
            Serial.print(" : | State : ");
            Serial.println(loopstate[i]);
        }
    #endif
}

void Memory::readPreset(uint8_t bank, uint8_t preset, uint8_t* loop, uint8_t* loopstate, uint8_t loopcount)
{
    uint16_t startAdress = c_presetSaveStartAddress + ((bank - 65) * c_presetBankSaveSize) + (c_presetSaveSize * preset);

    #ifdef DEBUG
        Serial.println("Reading preset : ");
    #endif

    #ifdef DEBUG
        Serial.print("Preset bank : ");
        Serial.println(bank);
    #endif

    #ifdef DEBUG
        Serial.print("Preset : ");
        Serial.println(preset);
    #endif

    startAdress += 2;

    eeprom0.readArray(startAdress, loop, loopcount);
    startAdress += loopcount;

    eeprom0.readArray(startAdress, loopstate, loopcount);
    startAdress += loopcount;

    #ifdef DEBUG
        for (uint8_t i = 0; i < loopcount; i++)
        {
            Serial.print("Loop ");
            Serial.print(loop[i]);
            Serial.print(" : | State : ");
            Serial.println(loopstate[i]);
        }
    #endif
}


void Memory::memoryTest()
{
    eeprom0.testInt8();
}