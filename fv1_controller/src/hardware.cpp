#define DEBUG 1

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

TemporarySwitch tapFsw(19, 1000); // Tap footswitch
LedDriver16 tapDivLed(21); // Tap Div LED
PwmLed tapLed(15); // Blinking tap LED

AnalogPot pot0(A4); // P0
AnalogPot pot1(A0); // P1
AnalogPot pot2(A3); // P2
AnalogPot pot3(A1); // Mix

DigitalPot dpot0(3); // Digital mix pot

FV1 fv1(14, 13, 12, 16, 17, 18); // FV1 DSP

void Hardware::hardwareSetup()
{
    midi.midiSetup();
    selectorLed.ledDriverSetup();
    tapDivLed.ledDriverSetup();
    mem.memorySetup();
    bypass.bypassSetup();
    selector.encoderSetup();
    bypassFsw.tempSwitchSetup();
    selectorSw.tempSwitchSetup();
    tapFsw.tempSwitchSetup();
    bypassLed.ledSetup();
    tapLed.ledSetup();
    pot0.analogPotSetup();
    pot1.analogPotSetup();
    pot2.analogPotSetup();
    pot3.analogPotSetup();
    dpot0.digitalPotSetup();
    fv1.FV1Setup();
}

void Hardware::hardwareInitialization()
{
    midi.setMidiChannel(mem.readMidiChannel()); // Restore the stored MIDI channel
}

void Hardware::hardwareStartup()
{
    while (millis() < 2000)
    {
        bypassFsw.tempSwitchPoll();
        selectorSw.tempSwitchPoll();
        tapFsw.tempSwitchPoll();
    }
}

void Hardware::restoreLastState()
{
    m_tapState = mem.readTapState(); // Read the tap state from memory
    m_divState = mem.readDivState(); // Read the div state from memory
    m_divValue = mem.readDivValue(); // Read the division value from memory
    m_interval = mem.readIntervalValue(); // Read the interval value from memory
    m_divInterval = mem.readDivIntervalValue(); // Read the divided interval value from memory
    m_presetMode = mem.readPresetMode(); // Read the stored preset mode
    m_currentPreset = mem.readCurrentPreset(); // Read the stored current preset
    m_currentProgram = mem.readCurrentProgram(); // Read the stored current program

    if (m_presetMode) // preset mode
    {
        selector.setCounter(m_currentPreset);
        loadPreset();
    }
    else // program mode
    {
        selector.setCounter(m_currentProgram); // Set the encoder counter        
        loadProgram();
    }

    m_bypassState = mem.readBypassState(); // Read the bypass state from memory
    turnPedalOnOff();   
}

void Hardware::hardwarePoll()
{
    bypassFsw.tempSwitchPoll(); // Poll the bypass footswitch

    if (bypassFsw.tempSwitchPushed()) // Bypass switch press
    {
        m_bypassSwitchPress = true; // Set the trigger
    }

    if (m_bypassState)
    {
        selectorSw.tempSwitchPoll(); // Poll the program selector switch

        if (selector.encoderPoll()) // Poll the program selector
        {
            if (m_presetMode)
            {
                m_currentPreset = selector.getCounter(); // Change the current program
            }
            else
            {
                m_currentProgram = selector.getCounter(); // Change the current preset
            }
            
            m_selectorMove = true; // Set the trigger
        }

        if (selectorSw.tempSwitchPushed()) // Selector switch press
        {
            m_selectorSwitchPress = true; // Set the trigger
        }

        if (selectorSw.tempSwitchLongPress()) // Selector switch long press
        {
            m_selectorSwitchLongPress = true; // Set the trigger
        }

        if (selectorSw.tempSwitchReleased())
        {
            m_selectorSwitchRelease = true;
        }

        if (m_effectHasTapEnabled)
        {
            tapFsw.tempSwitchPoll(); // Poll the tap footswitch

            if (tapFsw.tempSwitchPushed()) // Tap switch press
            {
                m_tapSwitchPress = true; // Set the trigger
            }

            if(tapFsw.tempSwitchLongPress()) // Tap switch long press
            {
                m_tapSwitchLongPress = true; // Set the trigger
            }
        }

        if (pot0.analogPotTurned()) // Pot0 moved
        {
            m_pot0Turned = true; // Set the trigger
        }

        if (pot1.analogPotTurned()) // Pot 1 moved
        {
            m_pot1Turned = true; // Set the trigger
        }

        if (pot2.analogPotTurned()) // Pot 2 moved
        {
            m_pot2Turned = true; // Set the trigger
        }

        if (pot3.analogPotTurned()) // Pot 3 moved
        {
            m_pot3Turned = true; // Set the trigger
        }
    }
}

void Hardware::resetTriggers()
{
    m_bypassSwitchPress = false;
    m_selectorMove = false;
    m_selectorSwitchPress = false;
    m_selectorSwitchLongPress = false;
    m_selectorSwitchRelease = false;
    m_tapSwitchPress = false;
    m_tapSwitchLongPress = false;
    m_pot0Turned = false;
    m_pot1Turned = false;
    m_pot2Turned = false;
    m_pot3Turned = false;
}

void Hardware::bypassSwitch()
{
    m_bypassState = !m_bypassState; // Switch the state
    mem.writeBypassState(m_bypassState); // Save to memory

    #ifdef DEBUG
        Serial.print("Bypass state switch, new state : ");
        Serial.println(m_bypassState);
    #endif

    turnPedalOnOff();
}

void Hardware::turnPedalOnOff()
{
    bypass.BypassSwitch(m_bypassState); // Send the state to the bypass object
    bypassLed.ledSetState(m_bypassState); // Send the state to the LED object

    if (m_bypassState)
    {
        if (m_presetMode)
        {
            selectorLed.lightLed(m_currentProgram);
        }
        else
        {
            selectorLed.lightLed(m_currentProgram + 8);
        }
    }
    else
    {
        selectorLed.lightAllLedOff();
        tapDivLed.lightAllLedOff();
        tapLed.ledTurnOff();
    }   
}

void Hardware::presetModeSwitch()
{
    m_presetMode = !m_presetMode; // Switch the preset mode
    m_currentProgram = 0; // Reset the program counter
    m_currentPreset = 0;
    selector.setCounter(0); // Set the selector counter

    mem.writePresetMode (m_presetMode); // Save to memory

    if (m_presetMode)
    {
        loadPreset(); // Load the preset
    }
    else
    {
        loadProgram(); // Load the program
    }

    #ifdef DEBUG
        Serial.print("Preset mode : ");
        Serial.println(m_presetMode);
    #endif
}

void Hardware::loadProgram()
{    
    m_effectIsDelay = programs[m_currentProgram].m_delayEffect; // Load program parameters
    m_effectHasPot0Enabled = programs[m_currentProgram].m_pot0Enabled; // Load program parameters
    m_effectHasPot1Enabled = programs[m_currentProgram].m_pot1Enabled; // Load program parameters
    m_effectHasPot2Enabled = programs[m_currentProgram].m_pot2Enabled; // Load program parameters
    m_effectHasPot3Enabled = programs[m_currentProgram].m_pot3Enabled; // Load program parameters

    fv1.sendProgramChange(m_currentProgram);
    mem.writeCurrentProgram(m_currentProgram);

    if (m_effectIsDelay) // Effect is a delay
    {
        m_effectMinInterval = programs[m_currentProgram].m_minInterval; // Load delay parameters
        m_effectMaxInterval = programs[m_currentProgram].m_maxInterval; // Load delay parameters
        m_effectHasTapEnabled = programs[m_currentProgram].m_tapEnabled; // Load delay parameters

        if (m_effectHasTapEnabled) // Effect has tap enabled
        {
            if (m_tapState) // Tap was active
            {
                if (m_divState) // Div was active
                {
                    tapDivLed.lightLed(m_divValue); // Light the div indicator

                    if (m_divInterval > m_effectMaxInterval) // Current interval over the max program value
                    {
                        m_divInterval = m_effectMaxInterval; // Set it to the max value
                    }
                    
                    if (m_divInterval < m_effectMinInterval) // Current interval under the min program value
                    {
                        m_divInterval = m_effectMinInterval; // Set it to the min value
                    }

                    fv1.sendPot0Value(getMappedDivInterval()); // Send the mapped interval value to the DSP
                }
                else // Div wasn't active
                {
                    if (m_interval > m_effectMaxInterval) // Current interval over the max program value
                    {
                        m_interval = m_effectMaxInterval; // Set it to the max value
                    }

                    if (m_interval < m_effectMinInterval) // Current interval under the min program value
                    {
                        m_interval = m_effectMinInterval; // Set it to the min value
                    }
                }

                fv1.sendPot0Value(getMappedMinMaxInterval()); // Send the mapped interval value to the DSP         
            }
            else // Tap wasn't active
            {
                fv1.sendPot0Value(pot0.getMappedCurrentPotValue()); // Send pot0 value tot he DSP
                setIntervalFromPotValue(pot0.getCurrentPotValue()); // Set the interval according to pot0 value
            }
        }
        else // Effect doesn't have tap enabled
        {
            fv1.sendPot0Value(pot0.getMappedCurrentPotValue()); // Send pot0 value to the DSP
            setIntervalFromPotValue(pot0.getCurrentPotValue()); // Set the interval according to pot0 value
        }
    }
    else // Effect isn't a delay
    {
        if (m_tapState) // Tap was enabled
        {
            m_tapState = 0; // Disable it
            mem.writeTapState(m_tapState); // Save it to memory
            tapLed.ledTurnOff(); // Turn the tap LED off

            if (m_divState) // Div was enabled
            {
                m_divState = 0; // Disable it
                mem.writeDivState(m_divState); // Save the state to memory
                m_divValue = 1; // Reset the div value
                mem.writeDivValue(m_divValue); // Save the value to memory
                tapDivLed.lightAllLedOff(); // Turn the div LED off
            }
        }
        
        if (m_effectHasPot0Enabled)
        {
            fv1.sendPot0Value(pot0.getMappedCurrentPotValue()); // Send pot0 value to the DSP
        }
    }

    if (m_effectHasPot1Enabled)
    {
        fv1.sendPot1Value(pot1.getMappedCurrentPotValue()); // Send pot1 value to the DSP
    }

    if (m_effectHasPot2Enabled)
    {
        fv1.sendPot2Value(pot2.getMappedCurrentPotValue()); // Send pot2 value to the DSP
    }

    if (m_effectHasPot3Enabled)
    {
        dpot0.setPotValue(pot3.getMappedCurrentPotValue());
    }

    selectorLed.lightLed(m_currentProgram + 8);
}

void Hardware::loadPreset()
{ 
    selectorLed.lightLed(map(m_currentPreset, 0, 7, 7, 0));
    mem.writeCurrentPreset(m_currentPreset); // Save the state
}

void Hardware::savePreset()
{
    tapLed.ledTurnOff();  // Turn off the tap LED
    selector.setCounter(0); // Reset the counter
    m_currentPreset = 0; // Reset the counter

    while (! selectorSw.tempSwitchReleased()) // Wait for the selector switch to be released after the long press
    {
        selectorLed.blinkLed(m_currentProgram, 100);
        selectorSw.tempSwitchPoll();
    }

    m_selectorSwitchRelease = false; // Reset the switch trigger
    m_presetSaveMode = true; // Set the trigger

    while (m_presetSaveMode)
    {
        selectorSw.tempSwitchPoll(); // Poll the selector switch

        selectorLed.blinkLed(m_currentPreset, 100); // Blink the current preset LED

        if (selector.encoderPoll()) // Encoder poll
        {
            m_currentPreset = selector.getCounter(); // Adjust the counter
            selectorLed.resetBlink(); // Reset the blink counter
            selectorLed.blinkLed(m_currentPreset, 100); // Blink the current preset LED
        }

        if (selectorSw.tempSwitchReleased())
        {
            m_presetSaveMode = false; // Reset the trigger
            m_selectorSwitchRelease = false; // Reset the switch trigger
            m_presetMode = 1; // Set the pedal in preset mode
            // mem.writePresetMode(1); // Save the state

            mem.writePreset(m_currentPreset, m_currentProgram, m_tapState, m_divState, m_divValue, m_interval, m_divInterval,
                            pot0.getCurrentPotValue(), pot1.getCurrentPotValue(), pot2.getCurrentPotValue(), pot3.getCurrentPotValue());

            loadPreset(); // Load the current preset
        }
    }
}

void Hardware::processTap()
{
    if ((m_timesTapped > 0) && ((millis() - m_lastTapTime) > (m_effectMaxInterval + 200))) // Timeout
    {
        m_timesTapped = 0; // Reset the tap count

        #ifdef DEBUG
            Serial.println("Tap timeout, reset");
        #endif
    }

    m_lastTapTime = tapFsw.getLastPushedTimes(); // Get the switch time

    if (m_timesTapped == 0) // First tap
    {
        m_firstTapTime = m_lastTapTime; // set the initial tap time
        m_timesTapped++; // Increment the counter

        #ifdef DEBUG
            Serial.print("Tap ");
            Serial.print(m_timesTapped);
            Serial.print(" : ");
            Serial.println(m_lastTapTime);
        #endif
    }
    else // Consecutive taps
    {
        m_timesTapped++; // Increment the counter

        #ifdef DEBUG
            Serial.print("Tap ");
            Serial.print(m_timesTapped);
            Serial.print(" : ");
            Serial.println(m_lastTapTime);
        #endif
    }

    if (m_timesTapped == c_maxTaps) // Tap count threshold
    {
        m_tapState = 1; // Enable tap
        mem.writeTapState(m_tapState); // Save it to memory
        m_timesTapped = 0; // Reset the tap count
        calculateInterval(); // Trigger the interval calculation

        #ifdef DEBUG
            Serial.println("Tap threshold");
        #endif
    }
}

void Hardware::processDiv()
{
    m_divState = 1; // Enable div
    mem.writeDivState(m_divState); // Save it to memory
    m_timesTapped = 0; // Reset the tap count

    if (m_divValue < 4) // Circle thru the division values
    {
        m_divValue ++;

        tapDivLed.lightLed(1 << (m_divValue -3));
    }
    else // Until the /1 then disable and reset
    {
        m_divState = 0; // Disable div
        mem.writeDivState(m_divState); // Save it to memory
        m_divValue = 1; // Reset the div value
        mem.writeDivValue(m_divValue); // Save it to memory
        tapDivLed.lightAllLedOff(); // Light the LEDs off
    }

    calculateDivInterval(); // Calculate the divided interval

    #ifdef DEBUG
        Serial.print("Div value : ");
        Serial.println(m_divValue);
    #endif
}

void Hardware::blinkTapLed()
{
    if (m_effectIsDelay)
    {
        if (m_divState) // Division is active, use the divided interval
        {
            m_tapLedBlinkValue = 128 + (127 * cos(2 * PI / m_divInterval * millis()));
        }
        else // Division not active
        {
            m_tapLedBlinkValue = 128 + (127 * cos(2 * PI / m_interval * millis()));
        }

        tapLed.setPwmLedState(m_tapLedBlinkValue);
    }
}

void Hardware::calculateInterval()
{
    m_interval = ((m_lastTapTime - m_firstTapTime) / (c_maxTaps - 1)); // Calculate the average tap value

    #ifdef DEBUG
        Serial.print("Interval : ");
        Serial.println(m_interval);
    #endif

    if (m_interval > m_effectMaxInterval) // Check against the program max interval and correct if necessary
    {
        m_interval = m_effectMaxInterval;

        #ifdef DEBUG
            Serial.print("Corrected interval : ");
            Serial.println(m_interval);
        #endif
    }

    if (m_interval < m_effectMinInterval) // Check against the program min interval and correct if necessary
    {
        m_interval = m_effectMinInterval;

        #ifdef DEBUG
            Serial.print("Corrected interval : ");
            Serial.println(m_interval);
        #endif
    }

    mem.writeIntervalValue(m_interval); // Save it to memory
    
    if (m_divState) // Division is enabled 
    {
        calculateDivInterval(); // Trigger the divided interval calculation
    }
    else // Division is not enabled
    {
        fv1.sendPot0Value(getMappedInterval()); // Send the mapped interval value to the DSP
    }
    
}

void Hardware::calculateDivInterval()
{
    m_divInterval = m_interval / m_divValue; // Current interval divided by current divider

    #ifdef DEBUG
        Serial.print("Division : ");
        Serial.println(m_divValue);
        Serial.print("Interval : ");
        Serial.println(m_divInterval);
    #endif
    
    if (m_divInterval < m_effectMinInterval) // Check against the program min interval and correct if necessary
    {
        m_divInterval = m_effectMinInterval;

        #ifdef DEBUG
            Serial.print("Corrected div interval : ");
            Serial.println(m_divInterval);
        #endif
    }

    mem.writeDivIntervalValue(m_divInterval); // Save it to memory
}

uint8_t Hardware::getMappedInterval()
{
    m_mappedInterval = map(m_interval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

    return m_mappedInterval;
}

uint8_t Hardware::getMappedDivInterval()
{
    m_mappedDivInterval = map(m_interval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

    return m_mappedDivInterval;
}

uint8_t Hardware::getMappedMinMaxInterval()
{
    m_mappedMinMaxInterval = map(m_interval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

    return m_mappedMinMaxInterval;
}

uint8_t Hardware::getMappedMinMaxDivInterval()
{
    m_mappedMinMaxDivInterval = map(m_divInterval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

    return m_mappedMinMaxDivInterval;
}

void Hardware::setIntervalFromPotValue(uint16_t value)
{
    m_interval = map(value, 0, 1023, m_effectMinInterval, m_effectMaxInterval);

    #ifdef DEBUG
        Serial.print("P0 interval : ");
        Serial.println(m_interval);
    #endif
}

void Hardware::processPot0()
{
    if (m_effectIsDelay) // Current effect is a delay
    {
        if (m_tapState) // Tap is enabled
        {
            m_tapState = 0; // Disable it
            mem.writeTapState(m_tapState); // Save it to memory

            if (m_divState) // Div is enabled
            {
                m_divState = 0; // Disable it
                mem.writeDivState(m_divState); // Save the state to memory
                m_divValue = 0; // Reset the div value
                mem.writeDivValue(m_divValue); // Save the value to memory
                tapDivLed.lightAllLedOff(); // Turn the LED off
            }
        }

        fv1.sendPot0Value(pot0.getMappedCurrentPotValue());
        setIntervalFromPotValue(pot0.getCurrentPotValue());
    }
    else // Current effect is not a delay
    {
        if (m_effectHasPot0Enabled)
        {
            fv1.sendPot0Value(pot0.getMappedCurrentPotValue());
        }
    }
}

void Hardware::processPot1()
{
    if (m_effectHasPot1Enabled)
    {
        fv1.sendPot1Value(pot1.getMappedCurrentPotValue());
    }
}

void Hardware::processPot2()
{
    if (m_effectHasPot2Enabled)
    {
        fv1.sendPot2Value(pot2.getMappedCurrentPotValue());
    }
}

void Hardware::processPot3()
{
    if (m_effectHasPot3Enabled)
    {
        dpot0.setPotValue(pot3.getMappedCurrentPotValue());
    }
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

bool Hardware::getSelectorSwitchReleased()
{
    return m_selectorSwitchRelease;
}

bool Hardware::getTapSwitchPress()
{
    return m_tapSwitchPress;
}

bool Hardware::getTapSwitchLongPress()
{
    return m_tapSwitchLongPress;
}

uint8_t Hardware::getBypassState()
{
    return m_bypassState;
}

bool Hardware::getPot0Turned()
{
    return m_pot0Turned;
}

bool Hardware::getPot1Turned()
{
    return m_pot1Turned;
}

bool Hardware::getPot2Turned()
{
    return m_pot2Turned;
}

bool Hardware::getPot3Turned()
{
    return m_pot3Turned;
}
