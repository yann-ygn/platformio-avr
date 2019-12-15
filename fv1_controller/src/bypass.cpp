#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(c_relayPin, OUTPUT);
    pinMode(c_okPin, OUTPUT),
    pinMode(c_switchPin, INPUT_PULLUP);

    digitalWrite(c_okPin, LOW);
    digitalWrite(c_relayPin, m_bypassState);
}

/*
bool Bypass::bypassPressed()
{
    m_switchState = digitalRead(c_switchPin);

    if (m_switchState == LOW 
    && m_now - m_lastPressTime > c_debounceTime 
    && m_switchState != m_lastSwitchState)
    {
        m_lastSwitchState = m_switchState;
        m_lastPressTime = m_now;        
        return true;
    }
    else
    {
        m_lastSwitchState = m_switchState;
        return false;
    }
}
*/

bool Bypass::bypassPressed()
{
    m_now = millis();

    if (m_now - m_lastPressTime > c_debounceTime )
    {
        m_lastPressTime = m_now;   
        return true;
    }
    else
    {
        return false;
    }
    
}

void Bypass::switchRelay()
{
    m_bypassState = !m_bypassState;

    digitalWrite(c_okPin, HIGH);            // OK on
    delay(10);                              // 5~10 ms depending on the OK
    digitalWrite(c_relayPin, m_bypassState);
    delay(10);                              // 5~10 ms depending on the relay
    digitalWrite(c_okPin, LOW);             // OK off
}

uint8_t Bypass::getBypassState()
{
    return m_bypassState;
}

void Bypass::setBypassState(uint8_t state)
{
    m_bypassState = state;
}