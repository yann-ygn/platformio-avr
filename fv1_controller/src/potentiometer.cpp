#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "potentiometer.h"

void Pot::potSetup()
{
    pinMode(m_pin, INPUT);
    m_currPotValue = analogRead(m_pin);
    m_lastPotValue = m_currPotValue;
}

bool Pot::potTurned()
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

uint8_t Pot::getMappedPotValue()
{
    return map(m_lastPotValue, 0, 1023, 0, 255); // Map to the 8 bits PWM res
}

uint16_t Pot::getCurrentPotValue()
{
    return m_currPotValue;
}

uint16_t Pot::getLastPotValue()
{
    return m_lastPotValue;
}

void DigitalPot::digitalPotSetup()
{
    pinMode(m_latchPin, OUTPUT);

    SPI.begin();

    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1));
    digitalWrite(m_latchPin, LOW);
    SPI.transfer(0b00011000);
    SPI.transfer(0b00000010);
    digitalWrite(m_latchPin, HIGH);
    SPI.endTransaction();
}

void DigitalPot::setPotValue(uint16_t value)
{
    uint8_t highByte = (value >> 8) + 0x04;
    uint8_t lowByte = (value & 0xFF);

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