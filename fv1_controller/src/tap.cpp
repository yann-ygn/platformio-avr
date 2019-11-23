#include <Arduino.h>

#include "tap.h"

void Tap::tapSetup()
{
    pinMode(c_swPin, INPUT_PULLUP);
    pinMode(c_ledPin, OUTPUT);
    pinMode(c_ledPinHalf, OUTPUT);
    pinMode(c_ledPinThird, OUTPUT);
    pinMode(c_ledPinQuarter, OUTPUT);

    digitalWrite(c_ledPin, LOW);
    digitalWrite(c_ledPinHalf, LOW);
    digitalWrite(c_ledPinThird, LOW);
    digitalWrite(c_ledPinQuarter, LOW);
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

uint8_t Tap::getTapCount()
{
    return m_timesTapped;
}

void Tap::setInterval()
{
    if (m_divEnabled)
    {
        m_interval = ((m_lastTaptime - m_firstTapTime) / c_maxTaps);
        m_newInterval = true;
    }
    else
    {
        m_interval = ((m_lastTaptime - m_firstTapTime) / c_maxTaps);
        m_newInterval = true;
    }    
}

int Tap::getInterval()
{
    return m_interval;
}

void Tap::blinkTapLed()
{
    m_blinkValue = 128 + (127 * cos(2 * PI / (m_interval * 2 ) * m_now)); // WIP try the whole range
    analogWrite(c_ledPin, m_blinkValue);
}

bool Tap::divPressed()
{
    if (m_tapState == LOW
    && m_now - m_lastTaptime > c_divDebounceTime
    && m_tapState == m_tapState
    && m_divEnabled == false)
    {
        m_tapState = m_lastTapState;
        m_lastTaptime = m_now;
        m_divEnabled = true;

        return true;
    }
    if (m_tapState == LOW
    && m_now - m_lastTaptime > c_divDebounceTime
    && m_tapState == m_lastTapState
    && m_divEnabled == true)
    {
        m_tapState = m_lastTapState;
        m_lastTaptime = m_now;

        return true;
    }
    else
    {
        m_tapState = m_lastTapState;

        return false;
    }    
}

void Tap::setDivision()
{
    if (m_divValue < 3)
    {
        m_divValue ++;
        m_newInterval = true;
    }
    else
    {
        m_divValue = 0;
        m_divEnabled = false;
        m_newInterval = true;
    }    
}

void Tap::lightDivLed()
{
    if (m_divEnabled)
    {
        switch (m_divValue)
        {
            case 1:
                digitalWrite(c_ledPinHalf, HIGH);
                break;

            case 2:
                digitalWrite(c_ledPinThird, HIGH);
                break;

            case 3:
                digitalWrite(c_ledPinQuarter, HIGH);
                break;
        }
    }
    else
    {
        digitalWrite(c_ledPinHalf, LOW);
        digitalWrite(c_ledPinThird, LOW);
        digitalWrite(c_ledPinQuarter, LOW);
    }    
}

int Tap::getDivision()
{
    return m_divValue;
}