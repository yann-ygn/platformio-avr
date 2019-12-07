#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(c_relayPin, OUTPUT);
    //pinMode(c_ledPin, OUTPUT);
    pinMode(c_okPin, OUTPUT),
    pinMode(c_switchPin, INPUT_PULLUP);

    digitalWrite(c_okPin, LOW);
    //digitalWrite(c_ledPin, m_relayState);
    digitalWrite(c_relayPin, m_relayState);
}

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

void Bypass::switchRelay()
{
    m_relayState = !m_relayState;

    digitalWrite(c_okPin, HIGH);            // OK on
    delay(10);                              // 5~10 ms depending on the OK
    digitalWrite(c_relayPin, m_relayState);
    //digitalWrite(c_ledPin, m_relayState);
    delay(10);                              // 5~10 ms depending on the relay
    digitalWrite(c_okPin, LOW);             // OK off
}