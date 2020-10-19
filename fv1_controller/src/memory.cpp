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
    #ifdef DEBUG
        Serial.println("Doing memory initialization");
    #endif

    writeMidiChannel(0);
    writeBypassState(0);
    writePresetMode(0);
    writeCurrentPreset(0);
    writeCurrentProgram(0);
    writeTapState(0);
    writeDivState(0);
    writeDivValue(1);
    writeDivIntervalValue(0);
    writeIntervalValue(0);

    writeInitialSetupState(1); // Initialization done
    #ifdef DEBUG
        Serial.println(readInitialSetupState());
    #endif
}

void Memory::memoryReset()
{
    #ifdef DEBUG
        Serial.println("Reset");
    #endif
    writeMidiChannel(0);
    writeBypassState(0);
    writePresetMode(0);
    writeCurrentPreset(0);
    writeCurrentProgram(0);
    writeTapState(0);
    writeDivState(0);
    writeDivValue(1);
    writeDivIntervalValue(0);
    writeIntervalValue(0);
    
    for (uint8_t i =0; i < 8; i++)
    {
        writeProgramExprSetting(i, 0);
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

uint8_t Memory::readCurrentProgram()
{
    uint8_t value = eeprom0.readInt8(c_currentProgramAddress);

    #ifdef DEBUG
        Serial.print("Reading current program : ");
        Serial.println(value);
    #endif

    return value;
}

void Memory::writeCurrentProgram(uint8_t program)
{
    #ifdef DEBUG
        Serial.print("Writing current program : ");
        Serial.println(program);
    #endif

    eeprom0.writeInt8(c_currentProgramAddress, program);
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

uint8_t Memory::readProgramExprSetting(uint8_t program)
{
    uint8_t setting = 0;

    switch (program)
    {
        case 0:
            setting = eeprom0.readInt8(c_program0ExpreSettingAddress);
            break;

        case 1:
            setting = eeprom0.readInt8(c_program1ExpreSettingAddress);
            break;

        case 2:
            setting = eeprom0.readInt8(c_program2ExpreSettingAddress);
            break;

        case 3:
            setting = eeprom0.readInt8(c_program3ExpreSettingAddress);
            break;

        case 4:
            setting = eeprom0.readInt8(c_program4ExpreSettingAddress);
            break;

        case 5:
            setting = eeprom0.readInt8(c_program5ExpreSettingAddress);
            break;
        
        case 6:
            setting = eeprom0.readInt8(c_program6ExpreSettingAddress);
            break;

        case 7:
            setting = eeprom0.readInt8(c_program7ExpreSettingAddress);
            break;

        default:
            break;
    }

    #ifdef DEBUG
        Serial.println("Reading program expression value");
        Serial.print("Program : ");
        Serial.println(program);
        Serial.print("Setting : ");
        Serial.println(setting);
    #endif

    return setting;
}

void Memory::writeProgramExprSetting(uint8_t program, uint8_t setting)
{
    switch (program)
    {
        case 0:
            eeprom0.writeInt8(c_program0ExpreSettingAddress, setting);
            break;

        case 1:
            eeprom0.writeInt8(c_program1ExpreSettingAddress, setting);
            break;

        case 2:
            eeprom0.writeInt8(c_program2ExpreSettingAddress, setting);
            break;

        case 3:
            eeprom0.writeInt8(c_program3ExpreSettingAddress, setting);
            break;

        case 4:
            eeprom0.writeInt8(c_program4ExpreSettingAddress, setting);
            break;

        case 5:
            eeprom0.writeInt8(c_program5ExpreSettingAddress, setting);
            break;
        
        case 6:
            eeprom0.writeInt8(c_program6ExpreSettingAddress, setting);
            break;

        case 7:
            eeprom0.writeInt8(c_program7ExpreSettingAddress, setting);
            break;

        default:
            break;
    }

    #ifdef DEBUG
        Serial.println("Writing program expression value");
        Serial.print("Program : ");
        Serial.println(program);
        Serial.print("Setting : ");
        Serial.println(setting);
    #endif
}

void Memory::readPreset(uint8_t preset, uint8_t * program, uint8_t * tap, uint8_t * div, uint8_t * divvalue, uint16_t * interval, 
                        uint16_t * divinterval, uint8_t * pot0, uint8_t * pot1, uint8_t * pot2, uint8_t * pot3)
{
    if (preset > 16)
    {
        preset = 16;
    }

    uint8_t data[12] = {};

    switch (preset)
    {
        case 0 : eeprom0.readArray(c_preset0Address, data, 12); break;
        case 1 : eeprom0.readArray(c_preset1Address, data, 12); break;
        case 2 : eeprom0.readArray(c_preset2Address, data, 12); break;
        case 3 : eeprom0.readArray(c_preset3Address, data, 12); break;
        case 4 : eeprom0.readArray(c_preset4Address, data, 12); break;
        case 5 : eeprom0.readArray(c_preset5Address, data, 12); break;
        case 6 : eeprom0.readArray(c_preset6Address, data, 12); break;
        case 7 : eeprom0.readArray(c_preset7Address, data, 12); break;
    }

    * program = data[0];
    * tap = data[1];
    * div = data[2];
    * divvalue = data[3];
    * interval = (data[5] << 8) + data[4];
    * divinterval = (data[7] << 8) + data[6];
    * pot0 = data[8];
    * pot1 = data[9];
    * pot2 = data[10];
    * pot3 = data[11];
    
    #ifdef DEBUG
        Serial.println("Reading");
        Serial.print("program : ");
        Serial.println(data[0]);
        Serial.print("tap : ");
        Serial.println(data[1]);
        Serial.print("div : ");
        Serial.println(data[2]);
        Serial.print("divvalue : ");
        Serial.println(data[3]);
        Serial.print("interval : ");
        Serial.println((data[5] << 8) + data[4]);
        Serial.print("divinterval : ");
        Serial.println((data[7] << 8) + data[6]);
        Serial.print("pot0 : ");
        Serial.println(data[8]);
        Serial.print("pot1 : ");
        Serial.println(data[9]);
        Serial.print("pot2 : ");
        Serial.println(data[10]);
        Serial.print("pot3 : ");
        Serial.println(data[11]);
    #endif
}

void Memory::writePreset(uint8_t preset, uint8_t program, uint8_t tap, uint8_t div, uint8_t divvalue, uint16_t interval, 
                        uint16_t divinterval, uint8_t pot0, uint8_t pot1, uint8_t pot2, uint8_t pot3)
{
    if (preset > 16)
    {
        preset = 16;
    }

    uint8_t data[12] = {};

    data[0] = program; // m_currentProgram
    data[1] = tap; // m_tapState
    data[2] = div; // m_divState
    data[3] = divvalue; // m_divValue
    data[4] = lowByte(interval); // m_interval
    data[5] = highByte(interval); // m_interval
    data[6] = lowByte(divinterval); // m_divInterval
    data[7] = highByte(divinterval); // m_divInterval
    data[8] = pot0; // pot0Value
    data[9] = pot1; // pot1Value
    data[10] = pot2; // pot2Value
    data[11] = pot3; // pot3Value

    #ifdef DEBUG
        Serial.println("Writing");
        Serial.print("program : ");
        Serial.println(data[0]);
        Serial.print("tap : ");
        Serial.println(data[1]);
        Serial.print("div : ");
        Serial.println(data[2]);
        Serial.print("divvalue : ");
        Serial.println(data[3]);
        Serial.print("interval : ");
        Serial.println((data[5] << 8) + data[4]);
        Serial.print("divinterval : ");
        Serial.println((data[7] << 8) + data[6]);
        Serial.print("pot0 : ");
        Serial.println(data[8]);
        Serial.print("pot1 : ");
        Serial.println(data[9]);
        Serial.print("pot2 : ");
        Serial.println(data[10]);
        Serial.print("pot3 : ");
        Serial.println(data[11]);
    #endif

    switch (preset)
    {
        case 0 : eeprom0.writeArray(c_preset0Address, data, 12); break;
        case 1 : eeprom0.writeArray(c_preset1Address, data, 12); break;
        case 2 : eeprom0.writeArray(c_preset2Address, data, 12); break;
        case 3 : eeprom0.writeArray(c_preset3Address, data, 12); break;
        case 4 : eeprom0.writeArray(c_preset4Address, data, 12); break;
        case 5 : eeprom0.writeArray(c_preset5Address, data, 12); break;
        case 6 : eeprom0.writeArray(c_preset6Address, data, 12); break;
        case 7 : eeprom0.writeArray(c_preset7Address, data, 12); break;
    }
}

void Memory::memoryTest()
{
    eeprom0.testInt8();
}