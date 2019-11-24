#include <Arduino.h>

#include "selector.h"

void Selector::selectorSetup()
{
    pinMode(m_encoderPinA, INPUT);
    pinMode(m_encoderPinB, INPUT);
    pinMode(m_encoderSwitch, INPUT);

    digitalWrite(m_encoderPinA, HIGH);
    digitalWrite(m_encoderPinB, HIGH);
}

void Selector::selectorMove()
{
    m_lastSelectorState = (digitalRead(m_encoderPinB) << 1) | digitalRead(m_encoderPinA);
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

bool Selector::selectorSwitch()
{

}
