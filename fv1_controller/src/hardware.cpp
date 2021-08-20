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
#include "expression.h"

Memory mem(22); // EEPROM

Midi midi; // MIDI

Bypass bypass(2, 1); // Relay + OK
TemporarySwitch bypassFsw(11, 1000); // Bypass footswitch
Led bypassLed(10); // Bypass LED

Encoder selector(A5, A6, 0, 7); // Program selector
TemporarySwitch selectorSw(A7, 1000); // Selector switch
LedDriver16 selectorLed(20); // Program LED

TemporarySwitch tapFsw(19, 1000); // Tap footswitch
LedDriver8 tapDivLed(21); // Tap Div LED
PwmLed tapLed(15); // Blinking tap LED

AnalogPot pot0(A4); // P0
AnalogPot pot1(A0); // P1
AnalogPot pot2(A3); // P2
AnalogPot pot3(A1); // Mix

Expr expr0(A2, 23); // Expression pedal

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
    expr0.exprSetup();
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
        pot0.analogPotTurned();
        pot1.analogPotTurned();
        pot2.analogPotTurned();

        if (expr0.exprPresent())
        {
            expr0.exprTurned();
        }
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

    for (uint8_t i = 0; i < 8; i++) // Read the stored expression pedal parameters
    {
        m_programExprSetting[i] = mem.readProgramExprSetting(i);
    }

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

    if (m_bypassState) // Effect is on
    {
        selectorSw.tempSwitchPoll(); // Poll the program selector switch

        if (m_presetMode) // Preset mode
        {
            tapFsw.tempSwitchPoll();

            if (selector.encoderPoll()) // Poll the program selector
            {
                m_currentPreset = selector.getCounter(); // Change the current program
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

            if (tapFsw.tempSwitchPushed())
            {
                m_tapSwitchPress = true;
            }

            if (tapFsw.tempSwitchLongPress())
            {
                m_tapSwitchLongPress = true;
            }

            if (tapFsw.tempSwitchReleased())
            {
                m_tapswitchRelease = true;
            }

            if (expr0.exprPresent()) // Expression pedal present
            {
                if (expr0.exprTurned()) // Expression pedal turned
                {

                }
            }
        }

        else // Program mode
        {
            if (selector.encoderPoll()) // Poll the program selector
            {
                m_currentProgram = selector.getCounter(); // Change the current preset
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

            if (expr0.exprPresent()) // Expression pedal present
            {
                if (expr0.exprTurned()) // Expression pedal turned
                {
                    m_exprTurned = true;
                }
            }
        }
    }

    else // Effect is off
    {
        tapFsw.tempSwitchPoll();

        if (tapFsw.tempSwitchLongPress())
        {
            m_tapSwitchLongPress = true;
        }
    }

    if (midi.completeMidiMessage()) // Complete midi message received
    {
        m_newMidiMessage = true; // Set the trigger
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
    m_tapswitchRelease = false;
    m_pot0Turned = false;
    m_pot1Turned = false;
    m_pot2Turned = false;
    m_pot3Turned = false;
    m_newMidiMessage = false;
    m_exprTurned = false;
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
            selectorLed.lightLed(7 - m_currentPreset);

            if (m_presetDivState)
            {
                tapDivLed.lightLed(m_presetDivValue);
            }
        }
        else
        {
            selectorLed.lightLed(m_currentProgram + 8);

            if (m_divState)
            {
                tapDivLed.lightLed(9 - m_divValue);
            }
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

    mem.writePresetMode(m_presetMode); // Save to memory

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
    m_programExprSetting[m_currentProgram] = mem.readProgramExprSetting(m_currentProgram); // Load the expr setting

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
                    if (m_bypassState)
                    {
                        tapDivLed.lightLed(5 - m_divValue); // Light the div indicator
                    }

                    if (m_divInterval > m_effectMaxInterval) // Current interval over the max program value
                    {
                        m_divInterval = m_effectMaxInterval; // Set it to the max value
                    }

                    if (m_divInterval < m_effectMinInterval) // Current interval under the min program value
                    {
                        m_divInterval = m_effectMinInterval; // Set it to the min value
                    }

                    fv1.sendPot0Value(getMappedMinMaxDivInterval()); // Send the mapped interval value to the DSP
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

                    fv1.sendPot0Value(getMappedMinMaxInterval()); // Send the mapped interval value to the DSP

                    tapDivLed.lightAllLedOff(); // Reset the tap LED
                }
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

        m_tapLedTurnOff = true; // Trigger the tap LED turn off
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

    if (m_bypassState)
    {
        selectorLed.lightLed(m_currentProgram + 8);
    }
}

void Hardware::loadPreset()
{
    mem.writeCurrentPreset(m_currentPreset);

    // Preset parameters
    uint8_t program = 0;
    m_presetTapState = 0;
    m_presetDivState = 0;
    m_presetDivValue = 0;
    m_presetInterval = 0;
    m_presetDivInterval = 0;
    uint8_t pot0 = 0;
    uint8_t pot1 = 0;
    uint8_t pot2 = 0;
    uint8_t pot3 = 0;
    m_presetExprSetting = 0;

    mem.readPreset(m_currentPreset, & program, & m_presetTapState, & m_presetDivState, & m_presetDivValue, & m_presetInterval, & m_presetDivInterval, & pot0, & pot1, & pot2, & pot3, & m_presetExprSetting); // Read the values from memory

    m_effectIsDelay = programs[program].m_delayEffect; // Load program parameters
    m_effectHasPot0Enabled = programs[program].m_pot0Enabled; // Load program parameters
    m_effectHasPot1Enabled = programs[program].m_pot1Enabled; // Load program parameters
    m_effectHasPot2Enabled = programs[program].m_pot2Enabled; // Load program parameters
    m_effectHasPot3Enabled = programs[program].m_pot3Enabled; // Load program parameters

    if (m_effectIsDelay)
    {
        m_effectMinInterval = programs[m_currentProgram].m_minInterval; // Load delay parameters
        m_effectMaxInterval = programs[m_currentProgram].m_maxInterval; // Load delay parameters
    }
    else
    {
        m_tapLedTurnOff = true; // Trigger the tap LED turn off
    }

    fv1.sendProgramChange(program); // Send the program change to the DSP

    if (m_presetTapState) // Preset with tap enabled
    {
        if (m_presetDivState) // Preset with div enabled
        {
            if (m_bypassState)
            {
                tapDivLed.lightLed(m_presetDivValue);
            }

            fv1.sendPot0Value(getPresetMappedMinMaxDivInterval());
        }
        else // Only tap
        {
            tapDivLed.lightAllLedOff();
            fv1.sendPot0Value(getPresetMappedMinMaxInterval());
        }
    }
    else // Tap not enabled
    {
        tapDivLed.lightAllLedOff();
        fv1.sendPot0Value(pot0);
    }

    if (m_effectHasPot1Enabled)
    {
        fv1.sendPot1Value(pot1);
    }

    if (m_effectHasPot2Enabled)
    {
        fv1.sendPot2Value(pot2);
    }

    if (m_effectHasPot3Enabled)
    {
        dpot0.setPotValue(pot3);
    }

    if (m_bypassState)
    {
        selectorLed.lightLed(7 - m_currentPreset); // Light the preset LED
    }
}

void Hardware::savePreset()
{
    tapLed.ledTurnOff();  // Turn off the tap LED
    selector.setCounter(0); // Reset the counter
    m_currentPreset = 0; // Reset the counter

    while (! selectorSw.tempSwitchReleased()) // Wait for the selector switch to be released after the long press
    {
        selectorLed.blinkLed(7 - m_currentPreset, 100);
        selectorSw.tempSwitchPoll();
    }

    m_selectorSwitchRelease = false; // Reset the switch trigger
    m_presetSaveMode = true; // Set the trigger

    while (m_presetSaveMode)
    {
        selectorSw.tempSwitchPoll(); // Poll the selector switch

        selectorLed.blinkLed(7 - m_currentPreset, 100); // Blink the current preset LED

        if (selector.encoderPoll()) // Encoder poll
        {
            m_currentPreset = selector.getCounter(); // Adjust the counter
            selectorLed.resetBlink(); // Reset the blink counter
            selectorLed.blinkLed(7 - m_currentPreset, 100); // Blink the current preset LED
        }

        if (selectorSw.tempSwitchReleased())
        {
            m_presetSaveMode = false; // Reset the trigger
            m_selectorSwitchRelease = false; // Reset the switch trigger
            m_presetMode = 1; // Set the pedal in preset mode
            mem.writePresetMode(m_presetMode); // Save the state

            mem.writePreset(m_currentPreset, m_currentProgram, m_tapState, m_divState, m_divValue, m_interval, m_divInterval,
                            pot0.getMappedCurrentPotValue(), pot1.getMappedCurrentPotValue(), pot2.getMappedCurrentPotValue(), 
                            pot3.getMappedCurrentPotValue(), m_programExprSetting[m_currentProgram]);

            mem.writeCurrentPreset(m_currentPreset); // Save the state
            loadPreset(); // Load the current preset
        }
    }
}

void Hardware::nextPreset()
{
    m_currentPreset ++;

    if (m_currentPreset == selector.getMaxCounterValue() + 1)
    {
        m_currentPreset = selector.getMinCounterValue();
    }

    selector.setCounter(m_currentPreset);
    loadPreset();
}

void Hardware::prevPreset()
{
    m_currentPreset --;

    if (m_currentPreset == 255 || m_currentPreset < selector.getMinCounterValue())
    {
        m_currentPreset = selector.getMaxCounterValue();
    }

    selector.setCounter(m_currentPreset);
    loadPreset();

    while (! tapFsw.tempSwitchReleased()) // Wait for the selector switch to be released after the long press
    {
        tapFsw.tempSwitchPoll();
    }

    m_tapswitchRelease = false; // Reset the switch trigger
}

void Hardware::processTap()
{
    if (! m_tapState) // Tap is not active, use the effect's max interval as timeout threshold
    {
        if ((m_timesTapped > 0) && ((millis() - m_lastTapTime) > (m_effectMaxInterval + 200))) // Timeout
        {
            m_timesTapped = 0; // Reset the tap count
            m_stillTapping = false; // Reset the continuous tap trigger

            #ifdef DEBUG
                Serial.println("Tap timeout, reset");
            #endif
        }
    }
    else // Tap is active
    {
        if (m_stillTapping) // Tap interval defined and still tapping, use the defined interval +- 20% as threshold
        {
            if (((millis() - m_lastTapTime) > m_interval + ((m_interval * 20) / 100)) || (millis() - m_lastTapTime) < (m_interval - ((m_interval * 20) / 100))) // Timeout
            {
                m_timesTapped = 0; // Reset the tap count
                m_stillTapping = false; // Reset the continuous tap trigger

                #ifdef DEBUG
                    Serial.println("Tap timeout, reset");
                #endif
            }
        }
        else // Tap is active but no interval has been defined yet, use the effect's max interval as timeout threshold
        {
            if ((m_timesTapped > 0) && ((millis() - m_lastTapTime) > (m_effectMaxInterval + 200))) // Timeout
            {
                m_timesTapped = 0; // Reset the tap count
                m_stillTapping = false; // Reset the continuous tap trigger

                #ifdef DEBUG
                    Serial.println("Tap timeout, reset");
                #endif
            }
        }
    }

    m_lastTapTime = tapFsw.getLastPushedTime(); // Get the switch time

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

    if (m_stillTapping) // Continous tapping
    {
        calculateInterval(); // Trigger the interval calculation
    }

    if (m_timesTapped == c_maxTaps) // Interval threshold to trigger the first interval calculation
    {
        m_tapState = 1; // Enable tap
        mem.writeTapState(m_tapState); // Save it to memory
        m_stillTapping = true; // Interval defined, set the continuous tapping trigger
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

    if (m_divValue < 5) // Circle thru the division values
    {
        m_divValue ++;

        if (m_presetMode)
        {
            if (m_bypassState)
            {
                tapDivLed.lightLed(5 - m_divValue);
            }
        }
        else
        {
            if (m_bypassState)
            {
                tapDivLed.lightLed(9 - m_divValue);
            }
        }
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
        if (m_presetMode) // Effect is in preset mode
        {
            if (m_presetDivState) // Division is active, use the divided interval
            {
                m_tapLedBlinkValue = 128 + (127 * cos(2 * PI / m_presetDivInterval * millis()));
            }
            else // Division not active
            {
                m_tapLedBlinkValue = 128 + (127 * cos(2 * PI / m_presetInterval * millis()));
            }

            tapLed.setPwmLedState(m_tapLedBlinkValue);
        }
        else // Program mode
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

    if (m_tapLedTurnOff)
    {
        tapLed.ledTurnOff();
        m_tapLedTurnOff = false;
    }
}

void Hardware::calculateInterval()
{
    m_interval = ((m_lastTapTime - m_firstTapTime) / (m_timesTapped - 1)); // Calculate the average tap value

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
        fv1.sendPot0Value(getMappedMinMaxInterval()); // Send the mapped interval value to the DSP
    }
}

void Hardware::calculateDivInterval()
{
    if (m_divValue < 5)
    {
        m_divInterval = m_interval / m_divValue; // Current interval divided by current divider
    }
    else
    {
        m_divInterval = m_interval * 0.75; // croche pointée
    }

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
    fv1.sendPot0Value(getMappedMinMaxDivInterval()); // Send the mapped interval to the DSP
}

uint8_t Hardware::getMappedInterval()
{
    m_mappedInterval = map(m_interval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

    return m_mappedInterval;
}

uint8_t Hardware::getMappedDivInterval()
{
    m_mappedDivInterval = map(m_divInterval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

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

uint8_t Hardware::getPresetMappedMinMaxInterval()
{
    m_mappedMinMaxInterval = map(m_presetInterval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

    return m_mappedMinMaxInterval;
}

uint8_t Hardware::getPresetMappedMinMaxDivInterval()
{
    m_mappedMinMaxDivInterval = map(m_presetDivInterval, m_effectMinInterval, m_effectMaxInterval, 0, 255);

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

void Hardware::setPresetIntervalFromPotValue(uint16_t value)
{
    m_presetInterval =  map(value, 0, 1023, m_effectMinInterval, m_effectMaxInterval);
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
                m_divValue = 1; // Reset the div value
                mem.writeDivValue(m_divValue); // Save the value to memory
                tapDivLed.lightAllLedOff(); // Turn the LED off
            }
        }

        fv1.sendPot0Value(pot0.getMappedCurrentPotValue());
        setIntervalFromPotValue(pot0.getCurrentPotValue());

        m_tapLedTurnOff = true; // Trigger a tap LED turn off to avoid weird blinking effects
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

void Hardware::processExpr()
{
    if (m_presetMode)
    {
        switch (m_presetExprSetting)
        {
        case 0:
            if (m_effectHasPot0Enabled)
            {
                if (m_effectIsDelay)
                {
                    if (m_presetDivState)
                    {
                        m_presetDivState = 0;
                        m_presetDivValue = 1;
                        tapDivLed.lightAllLedOff();
                    }

                    fv1.sendPot0Value(expr0.getMappedCurrExprValue());
                    setPresetIntervalFromPotValue(expr0.getCurrExprValue());

                    m_tapLedTurnOff = true;
                }
                else
                {
                    fv1.sendPot0Value(expr0.getMappedCurrExprValue());
                }
            }

            break;

        case 1:
            if (m_effectHasPot1Enabled)
            {
                fv1.sendPot1Value(expr0.getMappedCurrExprValue());
            }

            break;

        case 2:
            if (m_effectHasPot2Enabled)
            {
                fv1.sendPot2Value(expr0.getMappedCurrExprValue());
            }

            break;

        case 3:
            if (m_effectHasPot3Enabled)
            {
                dpot0.setPotValue(expr0.getMappedCurrExprValue());
            }

            break;

        default:
            break;
        }
    }
    else
    {
        switch (m_programExprSetting[m_currentProgram])
        {
            case 0:
                if (m_effectHasPot0Enabled)
                {
                    if (m_effectIsDelay)
                    {
                        if (m_tapState) // Tap is enabled
                        {
                            m_tapState = 0; // Disable it
                            mem.writeTapState(m_tapState); // Save it to memory

                            if (m_divState) // Div is enabled
                            {
                                m_divState = 0; // Disable it
                                mem.writeDivState(m_divState); // Save the state to memory
                                m_divValue = 1; // Reset the div value
                                mem.writeDivValue(m_divValue); // Save the value to memory
                                tapDivLed.lightAllLedOff(); // Turn the LED off
                            }
                        }

                        fv1.sendPot0Value(expr0.getMappedCurrExprValue());
                        setIntervalFromPotValue(expr0.getCurrExprValue());

                        m_tapLedTurnOff = true; // Trigger a tap LED turn off to avoid weird blinking effects
                    }
                    else
                    {
                        fv1.sendPot0Value(expr0.getMappedCurrExprValue());
                    }
                }

                break;

            case 1:
                if (m_effectHasPot1Enabled)
                {
                    fv1.sendPot1Value(expr0.getMappedCurrExprValue());
                }

                break;

            case 2:
                if (m_effectHasPot2Enabled)
                {
                    fv1.sendPot2Value(expr0.getMappedCurrExprValue());
                }

                break;

            case 3:
                if (m_effectHasPot3Enabled)
                {
                    dpot0.setPotValue(expr0.getMappedCurrExprValue());
                }

                break;
        }
    }
}

void Hardware::processMidiMessage()
{
    switch (midi.getCommandCode())
    {
        case MIDI_PC:
            if (midi.getDataByte1() < 8) // Program
            {
                if (m_presetMode == 1) // Not in program mode
                {
                    m_presetMode = 0; // Set the program mode
                    mem.writePresetMode(m_presetMode); // Write it to memory
                }

                m_currentProgram = midi.getDataByte1(); // Retrieve the program #
                selector.setCounter(m_currentProgram); // Set the selector counter
                loadProgram(); // Load the program

                midi.resetMidiMessage(); // Reset stored midi messages
            }

            else if (midi.getDataByte1() > 7 && midi.getDataByte1() < 16)
            {
                if (m_presetMode == 0) // Not in preset mode
                {
                    m_presetMode = 1; // Set the program mode
                    mem.writePresetMode(m_presetMode); // Write it to memory
                }

                m_currentPreset = midi.getDataByte1() - 8; // Retrieve the preset #
                selector.setCounter(m_currentPreset); // Set the selector counter
                loadPreset(); // Load the preset

                midi.resetMidiMessage(); // Reset stored midi messages
            }

            else
            {
                midi.resetMidiMessage(); // Reset stored midi messages
            }

            break;

        case MIDI_CC:
            switch (midi.getDataByte1())
            {
                case MIDI_BYPASS: // Bypass switch logic
                    if (midi.getDataByte2() == 0x00) // Turn off
                    {
                        if (m_bypassState) // Only process if the effect is on
                        {
                            m_bypassState = 0; // Set the bypass state
                            mem.writeBypassState(m_bypassState); // Write it to memory
                            turnPedalOnOff(); // Process
                        }

                        midi.resetMidiMessage(); // Reset stored midi messages
                    }

                    if (midi.getDataByte2() == 0x7F) // Turn on
                    {
                        if (! m_bypassState) // Only process if the effect is off
                        {
                            m_bypassState = 1; // Set the bypass state
                            mem.writeBypassState(m_bypassState); // Write it to memorys
                            turnPedalOnOff(); // Process
                        }

                        midi.resetMidiMessage(); // Reset stored midi messages
                    }

                    break;

                case MIDI_TAP: // Tap switch logic
                    if (midi.getDataByte2() == 0x7F && ! m_presetMode) // Tap trigger
                    {
                        tapFsw.setLastPushedTime(millis()); // Set the tap time
                        processTap(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else
                    {
                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                case MIDI_TAPLP: // Div switch logic
                    if (midi.getDataByte2() == 0x7F && ! m_presetMode) // Tap long press trigger
                    {
                        processDiv(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else
                    {
                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                case MIDI_DIV: // Div logic
                    if (midi.getDataByte2() == 0x01 && ! m_presetMode) // Div /1
                    {
                        if (m_divState) // Div was enabled
                        {
                            m_divState = 0; // Disable it
                            mem.writeDivState(m_divState); // Write to memory
                        }

                        m_divValue = 1; // Reset the div value
                        mem.writeDivValue(m_divValue); // Save to memory
                        tapDivLed.lightAllLedOff(); // Light the LEDs off
                        calculateDivInterval(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else if (midi.getDataByte2() == 0x02 && ! m_presetMode) // Div /2
                    {
                        if (! m_divState) // Div was not enabled
                        {
                            m_divState = 1; // Enable it
                            mem.writeDivState(m_divState); // Save to memory
                        }

                        m_divValue = 2; // Set the div value
                        mem.writeDivValue(m_divValue); // Write to memory

                        if (m_bypassState)
                        {
                            tapDivLed.lightLed(9 - m_divValue);
                        }

                        calculateDivInterval(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else if (midi.getDataByte2() == 0x03 && ! m_presetMode) // Div /3
                    {
                        if (! m_divState) // Div was not enabled
                        {
                            m_divState = 1; // Enable it
                            mem.writeDivState(m_divState); // Save to memory
                        }

                        m_divValue = 3; // Set the div value
                        mem.writeDivValue(m_divValue); // Write to memory

                        if (m_bypassState)
                        {
                            tapDivLed.lightLed(9 - m_divValue);
                        }

                        calculateDivInterval(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else if (midi.getDataByte2() == 0x04 && ! m_presetMode) // Div /4
                    {
                        if (! m_divState) // Div was not enabled
                        {
                            m_divState = 1; // Enable it
                            mem.writeDivState(m_divState); // Save to memory
                        }

                        m_divValue = 4; // Set the div value
                        mem.writeDivValue(m_divValue); // Write to memory

                        if (m_bypassState)
                        {
                            tapDivLed.lightLed(9 - m_divValue);
                        }

                        calculateDivInterval(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else if (midi.getDataByte2() == 0x05 && ! m_presetMode) // Div /5
                    {
                        if (! m_divState) // Div was not enabled
                        {
                            m_divState = 1; // Enable it
                            mem.writeDivState(m_divState); // Save to memory
                        }

                        m_divValue = 5; // Set the div value
                        mem.writeDivValue(m_divValue); // Write to memory

                        if (m_bypassState)
                        {
                            tapDivLed.lightLed(9 - m_divValue);
                        }

                        calculateDivInterval(); // Process

                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                    else
                    {
                        midi.resetMidiMessage(); // Reset stored midi messages
                        break;
                    }

                case MIDI_POT0:
                    pot0.setCurrentPotValue(midi.getDataByte2() * 8); // Set the pot value mapped to 10bits
                    processPot0(); // Process

                    midi.resetMidiMessage(); // Reset stored midi messages
                    break;

                case MIDI_POT1:
                    pot1.setCurrentPotValue(midi.getDataByte2() * 8); // Set the pot value mapped to 10bits
                    processPot1(); // Process

                    midi.resetMidiMessage(); // Reset stored midi messages
                    break;

                case MIDI_POT2:
                    pot2.setCurrentPotValue(midi.getDataByte2() * 8); // Set the pot value mapped to 10bits
                    processPot2(); // Process

                    midi.resetMidiMessage(); // Reset stored midi messages
                    break;

                case MIDI_POT3:
                    pot3.setCurrentPotValue(midi.getDataByte2() * 8); // Set the pot value mapped to 10bits
                    processPot3(); // Process

                    midi.resetMidiMessage(); // Reset stored midi messages
                    break;

                default:
                    break;
            }

        default:
            break;
    }
}

void Hardware::settingsMode()
{
    m_settingsMode = true; // Set the trigger
    m_menuLevel = 0; // Reset the lenu level
    m_menuItem = 0; // Reset the menu item
    selectorLed.lightLed(7 - m_menuItem); // Light the selector LED

    selector.setMinCounterValue(0); // Set the encoder min value for the main menu
    selector.setMaxCounterValue(1); // Set the encoder max value for the main menu
    selector.setCounter(0);

    while (m_settingsMode)
    {
        tapFsw.tempSwitchPoll(); // Poll the tap footswitch
        selectorSw.tempSwitchPoll(); // Poll the selector switch

        if (tapFsw.tempSwitchLongPress()) // Tap footswitch long press
        {
            m_settingsMode = false; // Exit the settings mode
        }

        if (selectorSw.tempSwitchReleased())
        {
            switch (m_menuLevel)
            {
                case 0: // Main menu
                    switch (m_menuItem)
                    {
                        case 0: // To midi settings
                            m_menuLevel = 1; // Enter midi menu
                            m_menuItem = 0; // Reset the menu item

                            selector.setMinCounterValue(0); // Set the encoder min value for the midi menu
                            selector.setMaxCounterValue(7); // Set the encoder max value for the midi menu
                            selector.setCounter(0); // Reset the selector counter
                            break;

                        case 1: // To expression pedal settings
                            m_menuLevel = 2; // Enter expression pedal menu
                            m_menuItem = 0; // Reset the menu item

                            selector.setMinCounterValue(0); // Set the encoder min value for the expression pedal menu
                            selector.setMaxCounterValue(7); // Set the encoder max value for the expression pedal menu
                            selector.setCounter(0); // Reset the selector counter

                            selectorLed.lightLed(m_menuItem + 8);
                            break;

                        default:
                            break;
                    }
                    break; // End main menu

                case 1: // Midi menu
                    mem.writeMidiChannel(m_menuItem); // Write the midi channel to memory
                    midi.setMidiChannel(m_menuItem); // Set the midi channel

                    m_menuLevel = 0; // Reset the menu level
                    m_menuItem = 0; // Reset the menu item
                    selectorLed.lightLed(7 - m_menuItem); // Light the selector LED

                    selector.setMinCounterValue(0); // Set the encoder min value for the main menu
                    selector.setMaxCounterValue(1); // Set the encoder max value for the main menu
                    selector.setCounter(0); // Reset the selector counter
                    break; // End midi menu

                case 2: // Expression pedal menu
                    m_selectedProgram = m_menuItem; // Store the program #
                    m_menuLevel = 3; // Enter expression pedal sub menu
                    m_menuItem = 0; // Reset the menu item

                    selector.setMinCounterValue(0); // Set the encoder min value for the expression pedal sub menu
                    selector.setMaxCounterValue(3); // Set the encoder max value for the expression pedal sub menu
                    selector.setCounter(0); // Reset the selector counter
                    break; // End expression pedal menu

                case 3:
                    mem.writeProgramExprSetting(m_selectedProgram, m_menuItem);
                    m_programExprSetting[m_selectedProgram] = m_menuItem;

                    m_menuLevel = 0; // Reset the menu level
                    m_menuItem = 0; // Reset the menu item
                    selectorLed.lightLed(7 - m_menuItem); // Light the selector LED

                    selector.setMinCounterValue(0); // Set the encoder min value for the main menu
                    selector.setMaxCounterValue(1); // Set the encoder max value for the main menu
                    selector.setCounter(0); // Reset the selector counter
                    break; // End expression pedal sub menu

                default:
                    break;
            }
        }

        if (m_menuLevel == 0) // Main menu
        {
            if (selector.encoderPoll())
            {
                m_menuItem = selector.getCounter();
                selectorLed.lightLed(7 - m_menuItem);
            }
        }

        if (m_menuLevel == 1) // Midi settings
        {
            if (selector.encoderPoll())
            {
                m_menuItem = selector.getCounter();
            }

            selectorLed.blinkLed(7 - m_menuItem, 100);
        }

        if (m_menuLevel == 2) // Expression pedal settings
        {
            if (selector.encoderPoll())
            {
                m_menuItem = selector.getCounter();
                selectorLed.lightLed(m_menuItem + 8);
            }
        }

        if (m_menuLevel == 3) // Expression pedal sub menu
        {
            if (selector.encoderPoll())
            {
                m_menuItem = selector.getCounter();
            }

            selectorLed.blinkLed(m_menuItem + 8, 100);
        }
    }

    selector.setMinCounterValue(0);
    selector.setMaxCounterValue(7);

    if(m_presetMode)
    {
        selector.setCounter(m_currentPreset);
    }

    else
    {
        selector.setCounter(m_currentProgram);
    }

    selectorLed.lightAllLedOff();
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

bool Hardware::getTapswitchRelease()
{
    return m_tapswitchRelease;
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

bool Hardware::getExprTurned()
{
    return m_exprTurned;
}

bool Hardware::getNewMidiMessage()
{
    return m_newMidiMessage;
}
