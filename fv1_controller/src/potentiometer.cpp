#define DEBUG 1

#include <Arduino.h>

#include "potentiometer.h"

void Pot::potSetup()
{
    pinMode(m_pin, INPUT);
    m_currPotValue = analogRead(m_pin);
    m_lastPotValue = m_currPotValue;
}

bool Pot::potTurned()
{
    m_currPotValue = analogRead(m_pin); // Read the current pot value

    if (abs(m_currPotValue - m_lastPotValue) > 3) // Slight noise debounce, if true save the value
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

uint8_t Pot::getMappedPotValue()
{
    return map(m_lastPotValue, 0, 1023, 0, 255); // Map to the 8 bits PWM res
}

uint16_t Pot::getCurrentPotValue()
{
    return m_currPotValue;
}

uint16_t Pot::getLastPotValue()
{
    return m_lastPotValue;
}