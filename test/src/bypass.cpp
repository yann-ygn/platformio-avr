#define DEBUG 1

#include <Arduino.h>

#include "bypass.h"

void Bypass::bypassSetup()
{
    pinMode(m_relayPin, OUTPUT);
    pinMode(m_okPin, OUTPUT),

    digitalWrite(m_okPin, LOW);
    digitalWrite(m_relayPin, m_bypassState);
}

void Bypass::bypassSwitchOn()
{
    m_bypassState = 1;

    digitalWrite(m_okPin, HIGH);                // OK on
    delay(10);                                  // 5~10 ms depending on the OK
    digitalWrite(m_relayPin, HIGH);             // Relay switch
    delay(10);                                  // 5~10 ms depending on the relay
    digitalWrite(m_okPin, LOW);                 // OK off

    #ifdef DEBUG
        Serial.print("Bypass : ");
        Serial.println(m_bypassState);
    #endif
}

void Bypass::bypassSwitchOff()
{
    m_bypassState = 0;

    digitalWrite(m_okPin, HIGH);                // OK on
    delay(10);                                  // 5~10 ms depending on the OK
    digitalWrite(m_relayPin, LOW);              // Relay switch
    delay(10);                                  // 5~10 ms depending on the relay
    digitalWrite(m_okPin, LOW);                 // OK off

    #ifdef DEBUG
        Serial.print("Bypass : ");
        Serial.println(m_bypassState);
    #endif
}

void Bypass::BypassSwitch()
{
    m_bypassState = !m_bypassState;

    digitalWrite(m_okPin, HIGH);                // OK on
    delay(10);                                  // 5~10 ms depending on the OK
    digitalWrite(m_relayPin, LOW);              // Relay switch
    delay(10);                                  // 5~10 ms depending on the relay
    digitalWrite(m_okPin, LOW);                 // OK off
}

uint8_t Bypass::getBypassState()
{
    return m_bypassState;
}

void Bypass::setBypassState(uint8_t state)
{
    m_bypassState = state;
}