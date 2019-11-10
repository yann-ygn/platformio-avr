#include <Arduino.h>

#include "potentiometer.h"

Pot::Pot(byte pin)
{
    m_pin = pin;
}

void Pot::potSetup()
{
    pinMode(m_pin, INPUT);
    m_currPotValue = readPotValue();
    m_lastPotValue = m_currPotValue;
}

int Pot::readPotValue()
{
    return analogRead(m_pin);
}

int Pot::getPotValue()
{
    return m_currPotValue;
}

bool Pot::potTurned()
{
    m_currPotValue = readPotValue();

    if (m_currPotValue > m_lastPotValue + 3 || m_currPotValue < m_lastPotValue - 3)
    {
        m_lastPotValue = m_currPotValue;
        return 1;
    }
    else
    {
        return 0;
    }
}