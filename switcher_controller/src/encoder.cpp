#define DEBUG 1

#include <Arduino.h>
#include "encoder.h"

void Encoder::encoderSetup()
{
    pinMode(m_encoderPinA, INPUT);
    pinMode(m_encoderPinB, INPUT);

    digitalWrite(m_encoderPinA, HIGH);
    digitalWrite(m_encoderPinB, HIGH);
}

uint8_t Encoder::readEncoderState()
{
    m_lastEncoderState = (digitalRead(m_encoderPinB) << 1) | digitalRead(m_encoderPinA);
    m_encoderState = c_encoderStates[m_encoderState & 0xf][m_lastEncoderState];

    return m_encoderState & 0x30;
}

bool Encoder::encoderPoll()
{
    uint8_t state = readEncoderState();

    if (state == 0x10)
    {
        m_counter --;
        if (m_counter == 255 || m_counter < m_minCounterValue)
        {
            m_counter = m_maxCounterValue;
        }
        #ifdef DEBUG
            Serial.print("Encoder counter decrement : ");
            Serial.println(m_counter);
        #endif

        return true;
    }

    else if (state == 0x20)
    {
        m_counter ++;
        if(m_counter == m_maxCounterValue + 1)
        {
            m_counter = m_minCounterValue;
        }
        #ifdef DEBUG
            Serial.print("Selector counter increment : ");
            Serial.println(m_counter);
        #endif

        return  true;
    }

    else
    {
        return false;
    }
}

uint8_t Encoder::getCounter()
{
    return m_counter;
}

void Encoder::setCounter(uint8_t counter)
{
    m_counter = counter;
}

uint8_t Encoder::getMinCounterValue()
{
    return m_minCounterValue;
}

uint8_t Encoder::getMaxCounterValue()
{
    return m_maxCounterValue;
}

void Encoder::setMinCounterValue(uint8_t value)
{
    m_minCounterValue = value;
}

void Encoder::setMaxCounterValue(uint8_t value)
{
    m_maxCounterValue = value;
}

uint8_t Encoder::getEncoderState()
{
    return m_encoderState;
}