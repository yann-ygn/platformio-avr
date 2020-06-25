#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>
#include "leddriver.h"

void LedDriver::ledDriverSetup()
{
    pinMode(m_csPin, OUTPUT);
    digitalWrite(m_csPin, HIGH);

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