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
    m_switchState = digitalRead(c_swPin); // Current footswitch state
    
    if (m_switchState == LOW                    // Footswitch is pressed
    && m_now - m_lastTaptime > c_debounceTime   // Past debounce time
    && m_switchState != m_lastSwitchState       // Went from high to low
    && !m_longTapPress)                         // No longtap press active
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
    if (m_timesTapped > 0                               // Tap counter is active
    && (m_now - m_lastTaptime) > (m_maxInterval + 200)) // Over the defined time out maxInterval * 1.2
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
    if (m_timesTapped == 0) // First tap, set the initial tap time
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

    if (m_timesTapped == c_maxTaps) // At the tap threshold, enable tap and trigger the interval calculation
    {
        m_tapState = 1;
        m_newInterval = true;
        tapReset();
    }
}

void Tap::calculateInterval()
{    
    m_interval = ((m_lastTaptime - m_firstTapTime) / (c_maxTaps - 1)); // Calculate the average tap value
    m_newInterval = false;

    #ifdef DEBUG
        Serial.print("Interval : ");
        Serial.println(m_interval);
    #endif

    if (m_interval > m_maxInterval) // Check against the program max interval and correct if necessary
    {
        m_interval = m_maxInterval;

        #ifdef DEBUG
            Serial.print("Corrected interval : ");
            Serial.println(m_interval);
        #endif
    }

    if (m_interval < m_minInterval) // Check against the program min interval and correct if necessary
    {
        m_interval = m_minInterval;

        #ifdef DEBUG
            Serial.print("Corrected interval : ");
            Serial.println(m_interval);
        #endif
    }
    
    if (m_divState) // Division is enabled trigger the div calculation
    {
        m_newDivInterval = true;
    }
}

void Tap::calculateDivInterval()
{
    m_divInterval = m_interval / m_divValue; // Current interval divided by current divider
    m_newDivInterval = false;

    #ifdef DEBUG
        Serial.print("Division : ");
        Serial.println(m_divValue);
        Serial.print("Interval : ");
        Serial.println(m_divInterval);
    #endif
    
    if(m_divInterval < m_minInterval) // Check against the program min interval and correct if necessary
    {
        m_divInterval = m_minInterval;

        #ifdef DEBUG
            Serial.print("Corrected div interval : ");
            Serial.println(m_divInterval);
        #endif
    }
}

void Tap::blinkTapLed(uint16_t interval)
{
    if (interval == 0) // No argument, use the member value
    {
        if (m_divState) // Division is active, use the divided interval
        {
            m_blinkValue = 128 + (127 * cos(2 * PI / m_divInterval * m_now)); // WIP try the whole range
        }
        else // Division not active
        {
            m_blinkValue = 128 + (127 * cos(2 * PI / m_interval * m_now)); // WIP try the whole range
        }
    }
    else // Argument, use it and map the value against the program min and max interval
    {
        m_blinkValue = 128 + (127 * cos(2 * PI / (map(interval, 0, 1024, m_minInterval, m_maxInterval)) * m_now)); // WIP try the whole range
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
    if (m_switchState == LOW                        // Footswitch is pressed
    && m_now - m_lastTaptime > c_divDebounceTime    // Past div debounce time
    && m_switchState == m_lastSwitchState           // Stayed pressed
    && m_divState == false                          // Div isn't enabled
    && m_interval > 0)                              // There's an active delay value
    {
        m_switchState = m_lastSwitchState;
        m_lastTaptime = m_now;
        m_longTapPress = true;
        m_divState = 1;

        return true;
    }
    else if (m_switchState == LOW                   // Footswitch is pressed
    && m_now - m_lastTaptime > c_divDebounceTime    // Past div debounce time
    && m_switchState == m_lastSwitchState           // Stayed pressed
    && m_divState == true)                          // Div is enabled
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
    if (m_divValue < 4) // Circle thru the division values
    {
        m_divValue ++;
        m_newDivInterval = true;
    }
    else                // Until the /1 then disable and reset
    {
        m_divValue = 1;
        m_divState = 0;
        m_newDivInterval = true;
        tapReset();
    }    
}

void Tap::lightDivLed()
{
    if (m_divState) // Div is enabled, light the correct LED according to the div value
    {
        shiftReg(1 << (m_divValue -1));
    }
    else // Div is disabled, turn off the LEDs
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

uint16_t Tap::getInterval()
{
    return m_interval;
}

void Tap::setInterval(uint16_t interval)
{
    m_interval = interval;
}

void Tap::setDivInterval(uint16_t interval)
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

uint16_t Tap::getMinInterval()
{
    return m_minInterval;
}

void Tap::setMinInterval(uint16_t interval)
{
    m_minInterval = interval;
}

uint8_t Tap::getMappedInterval()
{
    return map(m_interval, m_minInterval, m_maxInterval, 0, 255);
}

uint8_t Tap::getMappedDivInterval()
{
    return map(m_divInterval, m_minInterval, m_maxInterval, 0, 255);
}
