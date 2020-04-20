#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(m_relayPin, OUTPUT);
    pinMode(m_ledPin, OUTPUT);
    pinMode(m_led2Pin, OUTPUT);
    pinMode(m_okPin, OUTPUT),
    pinMode(m_switchPin, INPUT_PULLUP);

    digitalWrite(m_okPin, LOW);
    digitalWrite(m_ledPin, LOW);
    digitalWrite(m_led2Pin, LOW);
    digitalWrite(m_relayPin, LOW);
}

bool Bypass::bypassPressed()
{
    m_switchState = digitalRead(m_switchPin);

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

    digitalWrite(m_okPin, HIGH);            // OK on
    delay(10);                              // 5~10 ms depending on the OK
    digitalWrite(m_relayPin, m_relayState);
    delay(10);                              // 5~10 ms depending on the relay
    digitalWrite(m_okPin, LOW);             // OK off
}

void Bypass::switchActiveLed()
{
    m_activeLed = !m_activeLed;
}

void Bypass::lightActiveLed()
{
    if (m_activeLed)
    {
        digitalWrite(m_led2Pin, LOW);
        digitalWrite(m_ledPin, HIGH);
    }
    else
    {
        digitalWrite(m_ledPin, LOW);
        digitalWrite(m_led2Pin, HIGH);
    }
}

void Bypass::turnOffLed()
{
    digitalWrite(m_ledPin, LOW);
    digitalWrite(m_led2Pin, LOW);
}

uint8_t Bypass::getRelayState()
{
    return m_relayState;
}