#define DEBUG 1

#include <Arduino.h>

#include "potentiometer.h"

void Pot::potSetup()
{
    pinMode(m_pin, INPUT);
    m_currPotValue = analogRead(m_pin);
    m_lastPotValue = m_currPotValue;
}

int Pot::getPotValue()
{
    return m_currPotValue;
}

bool Pot::potTurned()
{
    m_currPotValue = analogRead(m_pin);

    if (abs(m_currPotValue - m_lastPotValue) > 3)
    {
        #ifdef DEBUG
            Serial.println(m_currPotValue);
        #endif

        m_lastPotValue = m_currPotValue;
        return true;
    }
    else
    {
        return false;
    }
}