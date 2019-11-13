#include <Arduino.h>

#include "tap.h"

void Tap::tapSetup()
{
    pinMode(m_tapPin, INPUT_PULLUP);
    pinMode(m_ledPin, OUTPUT);
}

bool Tap::tapPressed()
{
    m_tapState = digitalRead(m_tapPin);
    
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