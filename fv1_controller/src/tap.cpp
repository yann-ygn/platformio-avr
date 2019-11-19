#include <Arduino.h>

#include "tap.h"

void Tap::tapSetup()
{
    pinMode(c_swPin, INPUT_PULLUP);
    pinMode(c_ledPin, OUTPUT);
}

bool Tap::tapPressed()
{
    m_tapState = digitalRead(c_swPin);
    
    if (m_tapState == LOW 
    && m_now - m_lastTaptime > c_debounceTime 
    && m_tapState != m_lastTapState)
    {
        m_lastTaptime = m_now;
        m_lastTapState = m_tapState;
        return true;
    }
    else
    {
        m_lastTapState = m_tapState;
        return false;
    }
    
}

bool Tap::tapTimeout()
{
    if (m_timesTapped > 0 && (m_now - m_lastTaptime) > c_maxInterval * 1.5)
    {
        return true;
    }
    else
    {
        return false;
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
        m_timesTapped++;
    }
    else
    {
        m_timesTapped++;
    }
}

byte Tap::getTapCount()
{
    return m_timesTapped;
}

void Tap::setInterval()
{
    m_interval = ((m_lastTaptime - m_firstTapTime) / c_maxTaps);
    m_newInterval = 1;
}

int Tap::getInterval()
{
    return m_interval;
}