#include <Arduino.h>

#include "selector.h"

void Selector::selectorSetup()
{
    pinMode(c_encoderPinA, INPUT);
    pinMode(c_encoderPinB, INPUT);
    pinMode(c_switchPin, INPUT);

    digitalWrite(c_encoderPinA, HIGH);
    digitalWrite(c_encoderPinB, HIGH);
}

void Selector::selectorMove()
{
    m_lastSelectorState = (digitalRead(c_encoderPinB) << 1) | digitalRead(c_encoderPinA);
    m_selectorState = c_encoderStates[m_selectorState & 15][m_lastSelectorState];

    if (m_selectorState == 0x10)
    {
        m_counter --;
        if (m_counter < 0)
        {
            m_counter = 7;
        }
        m_newProgram = true;
    }
    if (m_selectorState == 0x20)
    {
        m_counter ++;
        if(m_counter > 7)
        {
            m_counter = 0;
        }
        m_newProgram = true;
    }
}

bool Selector::presetSwitch()
{
    m_switchState = digitalRead(c_switchPin);
    
    if (m_switchState == HIGH 
    && m_now - m_lastSwitchTime > c_debounceTime 
    && m_switchState != m_lastSwitchState)
    {
        m_lastSwitchTime = m_now;
        m_lastSwitchState = m_switchState;

        return true;
    }
    else
    {
        m_lastSwitchState = m_switchState;

        return false;
    }    
}

void Selector::setPresetMode()
{
    m_presetMode = !m_presetMode;
}
