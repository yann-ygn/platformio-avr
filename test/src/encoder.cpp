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
    m_lastSelectorState = (digitalRead(m_encoderPinB) << 1) | digitalRead(m_encoderPinA);
    m_selectorState = c_encoderStates[m_selectorState & 0xf][m_lastSelectorState];

    return m_selectorState & 0x30;
}

bool Encoder::encoderMove()
{
    uint8_t state = readEncoderState();

    
}