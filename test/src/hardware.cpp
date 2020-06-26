#include <Arduino.h>
#include "bypass.h"
#include "encoder.h"
#include "fv1.h"
#include "led.h"
#include "leddriver.h"
#include "memory.h"
#include "potentiometer.h"
#include "switch.h"
#include "midi.h"
#include "hardware.h"
#include "programs.h"

Memory mem(22); // EEPROM

Midi midi; // MIDI

Bypass bypass(2, 1); // Relay + OK
TemporarySwitch bypassFsw(11, 1000); // Bypass footswitch
Led bypassLed(10); // Bypass LED

Encoder selector(A5, A6, 0, 7); // Program selector
TemporarySwitch selectorSw(A7, 1000); // Selector switch
LedDriver16 selectorLed(20); // Program LED

void Hardware::hardwareSetup()
{
    midi.midiSetup();
    mem.memorySetup();
    bypass.bypassSetup();
    bypassFsw.tempSwitchSetup();
    bypassLed.ledSetup();
    selector.encoderSetup();
    selectorSw.tempSwitchSetup();
    selectorLed.ledDriverSetup();
}

void Hardware::hardwareInitialization()
{
    if (!mem.readInitialSetupState()) // Memory hasn't been initialized
    {
        mem.memoryInitialization();
    }

    midi.setMidiChannel(mem.readMidiChannel()); // Restore the stored MIDI channel
}

void Hardware::restoreLastState()
{
    m_bypassState = mem.readBypassState(); // Read the bypass state from memory
    bypass.BypassSwitch(m_bypassState); // Restore the bypass state
    bypassLed.setLedState(m_bypassState); // Restore the bypass LED state

    m_currentProgram = mem.readCurrentPreset(); // Read the stored current program
    selector.setCounter(m_currentProgram); // Set the encoder counter
    m_presetMode = mem.readPresetMode(); // Read the stored preset mode
    if (m_presetMode) // Light up the selector LED, preset mode
    {
        selectorLed.lightLed2(m_currentProgram);
    }
    else // program mode
    {
        selectorLed.lightLed(m_currentProgram);
    }
}

void Hardware::hardwarePoll()
{
    bypassFsw.tempSwitchPoll(); // Poll the bypass footswitch
    selectorSw.tempSwitchPoll(); // Poll the program selector switch

    if (selector.encoderPoll()) // Poll the program selector
    {
        m_currentProgram = selector.getCounter(); // Change the current program
        m_selectorMove = true; // Set the trigger
    }

    if (bypassFsw.tempSwitchPushed()) // Bypass switch press
    {
        m_bypassSwitchPress = true; // Set the trigger
    }

    if (selectorSw.tempSwitchPushed()) // Selector switch press
    {
        m_selectorSwitchPress = true; // Set the trigger
    }

    if (selectorSw.tempSwitchLongPress()) // Selector switch long press
    {
        m_selectorSwitchLongPress = true; // Set the trigger
    }
}

void Hardware::bypassSwitch()
{
    m_bypassState = !m_bypassState;
    bypass.BypassSwitch(m_bypassState);
    bypassLed.setLedState(m_bypassState);
}

void Hardware::presetModeSwitch()
{
    m_presetMode = !m_presetMode;
}

void Hardware::loadPreset()
{

}

void Hardware::loadProgram()
{

}

uint8_t Hardware::getCurrentProgram()
{
    return m_currentProgram;
}

uint8_t Hardware::getPresetMode()
{
    return m_presetMode;
}

bool Hardware::getBypassSwitchPress()
{
    return m_bypassSwitchPress;
}

bool Hardware::getSelectorMove()
{
    return m_selectorMove;
}

bool Hardware::getSelectorSwitchPress()
{
    return m_selectorSwitchPress;
}

bool Hardware::getSelectorSwitchLongPress()
{
    return m_selectorSwitchLongPress;
}

uint8_t Hardware::getBypassState()
{
    return m_bypassState;
}