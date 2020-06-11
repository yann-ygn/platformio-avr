#define DEBUG 1

#include <Arduino.h>
#include "led.h"

void Led::ledSetup()
{
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, m_ledState);
}

void Led::ledTurnOn()
{
    m_ledState = 1;
    digitalWrite(m_pin, m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.println(" on");
    #endif
}

void Led::ledTurnOff()
{
    m_ledState = 0;
    digitalWrite(m_pin, m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.println(" off");
    #endif
}

void Led::ledSwitchState()
{
    m_ledState = !m_ledState;
    digitalWrite(m_pin, m_ledState);

    #ifdef DEBUG
        Serial.print("LED ");
        Serial.print(m_pin);
        Serial.print(" switched state : ");
        Serial.println(m_ledState);
    #endif
}

uint8_t Led::getLedState()
{
    return m_ledState;
}

void Led::setLedState(uint8_t state)
{
    m_ledState = state;
}