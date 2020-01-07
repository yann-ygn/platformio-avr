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
    m_switchState = digitalRead(c_swPin);
    
    if (m_switchState == LOW 
    && m_now - m_lastTaptime > c_debounceTime 
    && m_switchState != m_lastSwitchState
    && !m_longTapPress)
    {
        m_lastTaptime = m_now;
        m_lastSwitchState = m_switchState;
        return true;
    }
    else
    {
        m_lastSwitchState = m_switchState;
        return false;
    }    
}

bool Tap::tapTimeout()
{
    if (m_timesTapped > 0 && (m_now - m_lastTaptime) > (m_maxInterval + 200))
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
        Serial.println("Tap reset");
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

    #ifdef DEBUG            
        Serial.print("Tap count : ");
        Serial.println(m_timesTapped);
        Serial.print("Now : ");
        Serial.println(m_now);
    #endif    

    if (m_timesTapped == c_maxTaps)
    {
        m_tapState = 1;
        m_newInterval = true;
        tapReset();
    }
}

uint8_t Tap::getTapCount()
{
    return m_timesTapped;
}

void Tap::calculateInterval()
{    
    if (m_newInterval)
    {
        m_interval = ((m_lastTaptime - m_firstTapTime) / (c_maxTaps - 1));
        m_newInterval = false;

        #ifdef DEBUG
            Serial.print("Interval : ");
            Serial.println(m_interval);
        #endif
        
        if (m_divState)
        {
            m_divInterval = m_interval / m_divValue;

            #ifdef DEBUG
                Serial.print("Division : ");
                Serial.println(m_divValue);
                Serial.print("Interval : ");
                Serial.println(m_divInterval);
            #endif

            if (m_divInterval > m_maxInterval)
            {
                m_divInterval = m_maxInterval;

                #ifdef DEBUG
                    Serial.print("Corrected div interval : ");
                    Serial.println(m_divInterval);
                #endif
            }
            
            if(m_divInterval < m_minInterval)
            {
                m_divInterval = m_minInterval;

                #ifdef DEBUG
                    Serial.print("Corrected div interval : ");
                    Serial.println(m_divInterval);
                #endif
            }
        }

        if (m_interval > m_maxInterval)
        {
            m_interval = m_maxInterval;

            #ifdef DEBUG
                Serial.print("Corrected interval : ");
                Serial.println(m_interval);
            #endif
        }

        if (m_interval < m_minInterval)
        {
            m_interval = m_minInterval;

            #ifdef DEBUG
                Serial.print("Corrected interval : ");
                Serial.println(m_interval);
            #endif
        }
    }
    
    if(m_newDivInterval)
    {
        m_divInterval = m_interval / m_divValue;
        lightDivLed();
        m_newDivInterval = false;

        #ifdef DEBUG
            Serial.print("Division : ");
            Serial.println(m_divValue);
            Serial.print("Interval : ");
            Serial.println(m_divInterval);
        #endif

        if (m_divInterval > m_maxInterval)
        {
            m_divInterval = m_maxInterval;

            #ifdef DEBUG
                Serial.print("Corrected div interval : ");
                Serial.println(m_divInterval);
            #endif
        }
        
        if(m_divInterval < m_minInterval)
        {
            m_divInterval = m_minInterval;

            #ifdef DEBUG
                Serial.print("Corrected div interval : ");
                Serial.println(m_divInterval);
            #endif
        }
    }
}

uint16_t Tap::getInterval()
{
    return m_interval;
}

void Tap::setInterval(uint16_t interval)
{
    m_interval = interval;
}

void Tap::blinkTapLed(uint16_t interval)
{
    if (interval == 0)
    {
        if (m_divState)
        {
            m_blinkValue = 128 + (127 * cos(2 * PI / m_divInterval * m_now)); // WIP try the whole range
        }
        else
        {
            m_blinkValue = 128 + (127 * cos(2 * PI / m_interval * m_now)); // WIP try the whole range
        }
    }
    else
    {
        m_blinkValue = 128 + (127 * cos(2 * PI / interval * m_now)); // WIP try the whole range
    }
    analogWrite(c_ledPin, m_blinkValue);
}

void Tap::turnOffTapLed()
{
    m_blinkValue = 0;

    analogWrite(c_ledPin, m_blinkValue);
}

bool Tap::divPressed()
{
    if (m_switchState == LOW
    && m_now - m_lastTaptime > c_divDebounceTime
    && m_switchState == m_lastSwitchState
    && m_divState == false
    && m_interval > 0)
    {
        m_switchState = m_lastSwitchState;
        m_lastTaptime = m_now;
        m_longTapPress = true;
        m_divState = 1;

        return true;
    }
    else if (m_switchState == LOW
    && m_now - m_lastTaptime > c_divDebounceTime
    && m_switchState == m_lastSwitchState
    && m_divState == true)
    {
        m_switchState = m_switchState;
        m_lastTaptime = m_now;

        return true;
    }
    else
    {
        m_switchState = m_lastSwitchState;

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
        m_divState = 0;
        m_newDivInterval = true;
        tapReset();
    }    
}

void Tap::setDivInterval(int interval)
{
    m_divInterval = interval;
}

uint16_t Tap::getDivInterval()
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
    if (m_divState)
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

uint8_t Tap::getTapState()
{
    return m_tapState;
}

void Tap::setTapState(uint8_t state)
{
    m_tapState = state;
}

uint8_t Tap::getDivState()
{
    return m_divState;
}

void Tap::setDivState(uint8_t state)
{
    m_divState = state;
}

uint16_t Tap::getMaxInterval()
{
    return m_maxInterval;
}

void Tap::setMaxInterval(uint16_t interval)
{
    m_maxInterval = interval;
}

uint8_t Tap::getMappedInterval()
{
    return map(m_interval, 0, 1000, 0, 255);
}

uint8_t Tap::getMappedDivInterval()
{
    return map(m_interval, m_minInterval, m_maxInterval, 0, 255);
}

uint16_t Tap::getMinInterval()
{
    return m_minInterval;
}

void Tap::setMinInterval(uint16_t interval)
{
    m_minInterval = interval;
}