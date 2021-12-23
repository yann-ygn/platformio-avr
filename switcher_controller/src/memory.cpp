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
    uint8_t startPresetBank = 65; // A
    uint8_t startPreset = 48; // 0
    uint8_t maxPresetBanks = 10; // Number of banks
    uint8_t maxPresets = 4; // Number of presets per banks
    uint8_t startLoop = 49; // 1
    uint8_t bufferLoop = 66; // B
    uint8_t maxLoops = 8; // Number of loops per preset

    uint8_t loops[maxLoops] = {0};
    uint8_t states[maxLoops] = {0};
    uint8_t orders[maxLoops] = {0};
    uint8_t* loopsptr = loops;
    uint8_t* statesptr = states;
    uint8_t* ordersptr = orders;

    for (uint8_t i = 0; i < maxLoops - 2; i++) // Last 2 loops are reserved for the internal buffers
    {
        loops[i] = startLoop + i;
    }

    loops[maxLoops - 1] = bufferLoop; // Buffer 1
    loops[maxLoops - 2] = bufferLoop; // Buffer 2

    for (uint8_t i = 0; i < maxLoops; i++)
    {
        orders[i] = i;
    }

    writeInitialSetupState(1);
    writeCurrentPresetBank(startPresetBank); // A
    writeCurrentPreset(startPreset); // 0

    for (uint8_t i = startPresetBank; i < startPresetBank + maxPresetBanks; i++)
    {
        for (uint8_t j = startPreset; j < startPreset + maxPresets; j++)
        {
            writePreset(i, &j, loopsptr, statesptr, ordersptr, maxLoops);
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
        Serial.print("Writing current preset : ");
        Serial.println(preset);
    #endif
}

void Memory::writePreset(uint8_t bank, uint8_t* preset, uint8_t* loopsid, uint8_t* loopsstate, uint8_t* loopsorder, uint8_t loopscount)
{
    uint16_t startAdress = c_presetSaveStartAddress + ((bank - 65) * c_presetBankSaveSize) + (c_presetSaveSize * (*preset - 48));

    #ifdef DEBUG
        Serial.print("Address : ");
        Serial.println(startAdress);
    #endif

    #ifdef DEBUG
        Serial.println("Writing preset : ");
    #endif

    eeprom0.writeInt8(startAdress, bank);
    startAdress++;

    #ifdef DEBUG
        Serial.print("Preset bank : ");
        Serial.println(bank);
    #endif

    eeprom0.writeInt8(startAdress, *preset);
    startAdress++;

    #ifdef DEBUG
        Serial.print("Preset : ");
        Serial.println(*preset);
    #endif

    eeprom0.writeArray(startAdress, loopsid, loopscount);
    startAdress += loopscount + 1;

    eeprom0.writeArray(startAdress, loopsstate, loopscount);
    startAdress += loopscount + 1;

    eeprom0.writeArray(startAdress, loopsorder, loopscount);
    startAdress += loopscount + 1;

    #ifdef DEBUG
        for (uint8_t i = 0; i < loopscount; i++)
        {
            Serial.print("Loop : ");
            Serial.print(loopsid[i]);
            Serial.print(" | Order : ");
            Serial.print(loopsorder[i]);
            Serial.print(" | State : ");
            Serial.println(loopsstate[i]);
        }
    #endif
}

void Memory::readPreset(uint8_t bank, uint8_t* preset, uint8_t* loopsid, uint8_t* loopsstate, uint8_t* loopsorder, uint8_t loopscount)
{
    uint16_t startAdress = c_presetSaveStartAddress + ((bank - 65) * c_presetBankSaveSize) + (c_presetSaveSize * (*preset));

    #ifdef DEBUG
        Serial.print("Address : ");
        Serial.println(startAdress);
    #endif


    #ifdef DEBUG
        Serial.println("Reading preset : ");
    #endif

    startAdress ++;

    #ifdef DEBUG
        Serial.print("Preset bank : ");
        Serial.println(bank);
    #endif

    eeprom0.readInt8(startAdress, preset);
    startAdress ++;

    #ifdef DEBUG
        Serial.print("Preset : ");
        Serial.println(*preset);
    #endif

    eeprom0.readArray(startAdress, loopsid, loopscount);
    startAdress += loopscount + 1;

    eeprom0.readArray(startAdress, loopsstate, loopscount);
    startAdress += loopscount + 1;

    eeprom0.readArray(startAdress, loopsorder, loopscount);
    startAdress += loopscount + 1;

    #ifdef DEBUG
        for (uint8_t i = 0; i < loopscount; i++)
        {
            Serial.print("Loop : ");
            Serial.print(loopsid[i]);
            Serial.print(" | Order : ");
            Serial.print(loopsorder[i]);
            Serial.print(" | State : ");
            Serial.println(loopsstate[i]);
        }
    #endif
}

void Memory::memoryTest()
{
    eeprom0.testInt8();
}