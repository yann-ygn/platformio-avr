#include <Arduino.h>

#include "tap.h"

Tap::Tap(byte pin, byte ledPin)
{
    m_pin = pin;
    m_ledPin = ledPin;
    m_timesTapped = 0;
    m_stillTaping = 0;
    m_tapState = 0;
    m_lastTapState = 0;
    m_lastTaptime = 0;
    m_firstTapTime = 0;
    m_interval = 0;
    m_now = 0;
    m_newInterval = 0;
}

void Tap::tapSetup()
{
    pinMode(m_pin, INPUT_PULLUP);
    pinMode(m_ledPin, OUTPUT);
}

bool Tap::tapPressed()
{
    m_tapState = digitalRead(m_pin);
    
    if (m_tapState == LOW && m_now - m_lastTaptime > 30 && m_tapState != m_lastTapState )
    {
        m_lastTaptime = m_now;
        return 1;
    }
}

bool Tap::tapTimeout()
{
    if (m_timesTapped > 0 && (m_now - m_lastTaptime) > c_maxInterval * 1.5)
    {
        return 1;
    }
}

void Tap::tapReset()
{
    m_timesTapped = 0;
}

void Tap::setTapCount()
{
    if (m_timesTapped == 0)
    {
        m_firstTapTime = m_now;
    }

    m_timesTapped++;
}

byte Tap::getTapCount()
{
    return m_timesTapped;
}

void Tap::setInterval()
{
    m_interval = ((m_firstTapTime - m_lastTaptime) / c_maxTaps);
    m_newInterval = 1;
}

int Tap::getInterval()
{
    return m_interval;
}