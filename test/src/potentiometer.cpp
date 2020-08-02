#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "potentiometer.h"

void AnalogPot::analogPotSetup()
{
    pinMode(m_pin, INPUT);
    m_currPotValue = analogRead(m_pin);
    m_lastPotValue = m_currPotValue;
}

bool AnalogPot::analogPotTurned()
{
    m_currPotValue = analogRead(m_pin); // Read the current pot value

    if (abs(m_currPotValue - m_lastPotValue) > 3) // Slight noise debounce, if true save the value
    {
        #ifdef DEBUG
            Serial.print("Pot ");
            Serial.print(m_pin);
            Serial.print(" : ");
            Serial.println(m_currPotValue);
        #endif

        m_lastPotValue = m_currPotValue;
        return true;
    }
    else
    {
        return false;
    }
}

uint8_t AnalogPot::getMappedCurrentPotValue()
{
    return m_lastPotValue >> 2; // 10 bits to 8 bits
}

uint16_t AnalogPot::getCurrentPotValue()
{
    return m_currPotValue;
}

void AnalogPot::setCurrentPotValue(uint16_t value)
{
    m_currPotValue = value;
}

uint16_t AnalogPot::getLastPotValue()
{
    return m_lastPotValue;
}

void DigitalPot::digitalPotSetup()
{
    pinMode(m_latchPin, OUTPUT);
    digitalWrite(m_latchPin, HIGH);

    SPI.begin();
}

void DigitalPot::setPotValue(uint16_t value)
{
    uint8_t highByte = highByte(value);
    uint8_t lowByte = lowByte(value);

    #ifdef DEBUG
        Serial.print("Dpot : ");
        Serial.println(value);
        Serial.print("HB : ");
        Serial.println(highByte);
        Serial.print("LB : ");
        Serial.println(lowByte);
    #endif

    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1));
    digitalWrite(m_latchPin, LOW);
    SPI.transfer(highByte);
    SPI.transfer(lowByte);
    digitalWrite(m_latchPin, HIGH);
    SPI.endTransaction();
}