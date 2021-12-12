#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>
#include "leddriver.h"

void LedDriver::ledDriverSetup()
{
    pinMode(m_csPin, OUTPUT);
    digitalWrite(m_csPin, LOW);

    SPI.begin();
}

void LedDriver::select()
{
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
    digitalWrite(m_csPin, LOW);
}

void LedDriver::deselect()
{
    digitalWrite(m_csPin, HIGH);
    digitalWrite(m_csPin, LOW);
    SPI.endTransaction();
}

void LedDriver8::lightLed(uint8_t led)
{
    select();
    SPI.transfer(1 << led);
    deselect();
}

void LedDriver8::lightAllLedOff()
{
    select();
    SPI.transfer(0);
    deselect();
}

void LedDriver16::lightLed(uint8_t led)
{
    select();
    SPI.transfer16(1 << led);
    deselect();
}

void LedDriver16::lightLed2(uint8_t led)
{
    select();
    SPI.transfer16(((1 << led) << 8) + (1 << led));
    deselect();
}

void LedDriver16::lightAllLedOff()
{
    select();
    SPI.transfer16(0);
    deselect();
}

void LedDriver16::blinkLed(uint8_t led, uint8_t interval)
{
    m_blinkTime = millis();

    if ((m_blinkTime - m_lastBlinkTime) >= interval)
    {
        if (m_lastBlinkState)
        {
            m_lastBlinkState = 0;
            lightAllLedOff();
        }
        else
        {
            m_lastBlinkState = 1;
            lightLed(led);
        }

        m_lastBlinkTime = m_blinkTime;
    }
}

void LedDriver16::blinkLed2(uint8_t led, uint8_t interval)
{
    m_blinkTime = millis();

    if ((m_blinkTime - m_lastBlinkTime) >= interval)
    {
        if (m_lastBlinkState)
        {
            m_lastBlinkState = 0;
            lightAllLedOff();
        }
        else
        {
            m_lastBlinkState = 1;
            lightLed2(led);
        }

        m_lastBlinkTime = m_blinkTime;
    }
}


void LedDriver16::resetBlink()
{
    m_lastBlinkTime = 0;
    m_lastBlinkState = 0;
}

void LedDriver16::setLedStateByMask(uint16_t mask)
{
    m_ledDriverMask = mask;

    select();
    SPI.transfer16(mask);
    deselect();
}

uint16_t LedDriver16::getLedDriverMask()
{
    return m_ledDriverMask;
}

#ifdef DEBUG
    void LedDriver8::testAllLed()
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            lightLed(i);
            delay(500);
            lightAllLedOff();
            delay(500);
        }
    }

    void LedDriver16::testAllLed()
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            lightLed(i);
            delay(500);
            lightAllLedOff();
            delay(500);
        }

        for (uint8_t i = 0; i < 8; i++)
        {
            lightLed2(i);
            delay(500);
            lightAllLedOff();
            delay(500);
        }
    }
#endif