#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "fv1.h"

void FV1::FV1Setup()
{
    pinMode(m_p0Pin, OUTPUT);
    pinMode(m_p1Pin, OUTPUT);
    pinMode(m_p2Pin, OUTPUT);

    pinMode(m_s0Pin, OUTPUT);
    pinMode(m_s1Pin, OUTPUT);
    pinMode(m_s2Pin, OUTPUT);

    analogWrite(m_p0Pin, 0);
    analogWrite(m_p1Pin, 0);
    analogWrite(m_p2Pin, 0);

    digitalWrite(m_s0Pin, LOW);
    digitalWrite(m_s1Pin, LOW);
    digitalWrite(m_s2Pin, LOW);
}

void FV1::sendProgramChange(uint8_t program)
{
    digitalWrite(m_s0Pin, HIGH && (program & 0x1));
    digitalWrite(m_s1Pin, HIGH && (program & 0x2));
    digitalWrite(m_s2Pin, HIGH && (program & 0x4));
}

void FV1::sendPot0Value(uint8_t value)
{
    analogWrite(m_p0Pin, value);
}

void FV1::sendPot1Value(uint8_t value)
{
    analogWrite(m_p1Pin, value);
}

void FV1::sendPot2Value(uint8_t value)
{
    analogWrite(m_p2Pin, value);
}
