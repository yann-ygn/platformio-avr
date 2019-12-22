#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "tap.h"

void Tap::tapSetup()
{
    pinMode(c_swPin, INPUT_PULLUP);
    pinMode(c_ledPin, OUTPUT);
    pinMode(c_latchPin, OUTPUT);

    digitalWrite(c_ledPin, LOW);
    digitalWrite(c_latchPin, LOW);

    SPI.begin();

    shiftReg(0);
}

bool Tap::tapPressed()
{
    m_tapState = digitalRead(c_swPin);
    
    if (m_tapState == LOW 
    && m_now - m_lastTaptime > c_debounceTime 
    && m_tapState != m_lastTapState
    && !m_longTapPress)
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
    m_longTapPress = false;

    #ifdef DEBUG
        Serial.println("Reset");
    #endif
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

    if (m_timesTapped == c_maxTaps)
    {
        m_newInterval = true;
    }

    #ifdef DEBUG            
        Serial.println("Tap count : ");
        Serial.println(m_timesTapped);
        Serial.println(m_now);
    #endif    
}

uint8_t Tap::getTapCount()
{
    return m_timesTapped;
}

void Tap::calculateInterval()
{    
    if (m_newInterval)
    {
        if (m_divEnabled)
        {
            m_divInterval = m_interval / m_divValue;
        }
        m_interval = ((m_lastTaptime - m_firstTapTime) / c_maxTaps);
        m_newInterval = false;

        #ifdef DEBUG
            Serial.println("Interval :");
            Serial.println(m_interval);
        #endif
    }
    
    if(m_newDivInterval)
    {
        m_divInterval = m_interval / m_divValue;
        lightDivLed();
        m_newDivInterval = false;

        #ifdef DEBUG
            Serial.println("Division :");
            Serial.println(m_divValue);
            Serial.println("Interval :");
            Serial.println(m_divInterval);
        #endif
    }
}

int Tap::getInterval()
{
    return m_interval;
}

void Tap::setInterval(int interval)
{
    m_interval = interval;
}

void Tap::blinkTapLed()
{
    if (m_divEnabled)
    {
        m_blinkValue = 128 + (127 * cos(2 * PI / (m_divInterval * 2 ) * m_now)); // WIP try the whole range
        analogWrite(c_ledPin, m_blinkValue);
    }
    else
    {
        m_blinkValue = 128 + (127 * cos(2 * PI / (m_interval * 2 ) * m_now)); // WIP try the whole range
        analogWrite(c_ledPin, m_blinkValue);
    }
}    

bool Tap::divPressed()
{
    if (m_tapState == LOW
    && m_now - m_lastTaptime > c_divDebounceTime
    && m_tapState == m_tapState
    && m_divEnabled == false
    && m_interval > 0)
    {
        m_tapState = m_lastTapState;
        m_lastTaptime = m_now;
        m_longTapPress = true;
        m_divEnabled = true;

        return true;
    }
    else if (m_tapState == LOW
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
    if (m_divValue < 4)
    {
        m_divValue ++;
        m_newDivInterval = true;
    }
    else
    {
        m_divValue = 1;
        m_divEnabled = false;
        m_newDivInterval = true;
    }    
}

void Tap::setDivInterval(int interval)
{
    m_divInterval = interval;
}

int Tap::getDivInterval()
{
    return m_divInterval;
}

uint8_t Tap::getDivValue()
{
    return m_divValue;
}

void Tap::setDivValue(uint8_t value)
{
    m_divValue = value;
}

void Tap::lightDivLed()
{
    if (m_divEnabled)
    {
        shiftReg(1 << (m_divValue -1));
    }
    else
    {
        shiftReg(0);
    }
    
}

void Tap::shiftReg(uint8_t value)
{
    SPI.beginTransaction(SPISettings(30000000, MSBFIRST, SPI_MODE0));
    digitalWrite(c_latchPin, LOW);
    SPI.transfer(value);
    digitalWrite(c_latchPin, HIGH);
    digitalWrite(c_latchPin, LOW);
    SPI.endTransaction();
}