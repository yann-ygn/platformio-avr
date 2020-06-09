#include <Arduino.h>

#include "footswitch.h"

void Footswitch::footswitchSetup()
{

}

void Footswitch::footswitchUpdate()
{
    m_now = millis();
    m_switchState = digitalRead(m_pin);

    if (m_switchState != m_lastSwitchState)
    {
        m_lastPressTime = m_now;
    }
}