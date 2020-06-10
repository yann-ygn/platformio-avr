#include <Arduino.h>

#include "footswitch.h"

void Footswitch::footswitchSetup()
{
    pinMode(m_pin, INPUT_PULLUP);
}

void Footswitch::footswitchPoll()
{
    m_footswitchState = digitalRead(m_pin);
    m_now = millis();

    if (m_footswitchState == m_lastFootswithState)
    {
        m_rawState = 1;
    }
    else
    {
        m_rawState = 0;
        m_deglitchTime = m_now;
    }
    
    if (m_rawState && ((m_now - m_deglitchTime) > m_deglitchPeriod))
    {
        m_deglitchedState = m_footswitchState;
        m_deglitchTime = m_now;
    }

    m_lastFootswithState = m_footswitchState;

    m_footswitchSwitched = 0;

    if ((m_deglitchedState != m_debouncedState) && (m_now - m_lastSwitchedTime) > m_debouncePeriod)
    {
        m_debouncedState = m_deglitchedState;
        m_footswitchSwitched = 1;
    }

    m_footswitchLongPress = 0;

    if (footswitchReleased())
    {
        m_longPressActive = false;
    }

    if (!m_longPressActive)
    {
        m_footswitchLongPress = !footswitchSwitched() && footswitchOn() &&((m_now - m_lastPushedTime) > m_longPressPeriod);
        m_longPressActive = m_footswitchLongPress;
    }

    if (footswitchSwitched())
    {
        m_lastSwitchedTime = m_now;

        if (footswitchPushed())
        {
            m_lastPushedTime = m_now;
        }
    }
}

bool Footswitch::footswitchSwitched()
{
    return m_footswitchSwitched;
}

bool Footswitch::footswitchOn()
{
    return !m_debouncedState;
}

bool Footswitch::footswitchPushed()
{
    return m_footswitchSwitched && !m_debouncedState;
}

bool Footswitch::footswitchReleased()
{
    return m_footswitchSwitched && m_debouncedState;
}

bool Footswitch::footswitchLongPress()
{
    return m_footswitchLongPress;
}