#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(m_relayPin, OUTPUT);
    pinMode(m_ledPin, OUTPUT);
    pinMode(m_okPin, OUTPUT),
    pinMode(m_switchPin, INPUT_PULLUP);
    pinMode(m_startupPin, INPUT_PULLUP);

    m_relayState = digitalRead(m_startupPin);
    digitalWrite(m_okPin, LOW);
    digitalWrite(m_ledPin, m_relayState);
    digitalWrite(m_relayPin, m_relayState);
}

boolean Bypass::bypassPressed()
{
    m_switchState = digitalRead(m_switchPin);

    if (m_switchState == LOW 
        && m_now - m_lastPressTime > c_debounceTime 
        && m_switchState != m_lastSwtichState)
    {
        m_lastPressTime = m_now;        
        return true;
    }
    else
    {
        m_lastSwtichState = m_switchState;
        return false;
    }
}

void Bypass::switchRelay()
{
    m_relayState = !m_relayState;

    digitalWrite(m_okPin, HIGH);
    delay(10);
    digitalWrite(m_relayPin, m_relayState);
    digitalWrite(m_ledPin, m_relayState);
    delay(10);
    digitalWrite(m_okPin, LOW);
}