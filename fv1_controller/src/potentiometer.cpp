#define DEBUG 1

#include <Arduino.h>

#include "potentiometer.h"

void Pot::potSetup()
{
    pinMode(m_pin, INPUT);
    m_currPotValue = analogRead(m_pin);
    m_lastPotValue = m_currPotValue;
}

uint8_t Pot::getMappedPotValue()
{
    return map(m_lastPotValue, 0, 1023, 0, 255);
}

uint16_t Pot::getCurrentPotValue()
{
    return m_currPotValue;
}

uint16_t Pot::getLastPotValue()
{
    return m_lastPotValue;
}

bool Pot::potTurned()
{
    m_currPotValue = analogRead(m_pin);

    if (abs(m_currPotValue - m_lastPotValue) > 3)
    {
        #ifdef DEBUG
            Serial.print("Pot ");
            Serial.print(m_pin);
            Serial.print(" : ");
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
