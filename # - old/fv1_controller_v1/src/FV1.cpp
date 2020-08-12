#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "FV1.h"

void FV1::FV1Setup()
{
    pinMode(c_pot0Pin, OUTPUT);
    pinMode(c_pot1Pin, OUTPUT);
    pinMode(c_pot2Pin, OUTPUT);

    pinMode(c_s0Pin, OUTPUT);
    pinMode(c_s1Pin, OUTPUT);
    pinMode(c_s2Pin, OUTPUT);

    analogWrite(c_pot0Pin, 0);
    analogWrite(c_pot1Pin, 0);
    analogWrite(c_pot2Pin, 0);

    digitalWrite(c_s0Pin, LOW);
    digitalWrite(c_s1Pin, LOW);
    digitalWrite(c_s2Pin, LOW);
}

void FV1::sendProgramChange(uint8_t program)
{
    digitalWrite(c_s0Pin, HIGH && (program & B00000001));
    digitalWrite(c_s1Pin, HIGH && (program & B00000010));
    digitalWrite(c_s2Pin, HIGH && (program & B00000100));
}

void FV1::sendPot0Value(int value)
{
    analogWrite(c_pot0Pin, value);
}

void FV1::sendPot1Value(int value)
{
    analogWrite(c_pot1Pin, value);
}

void FV1::sendPot2Value(int value)
{
    analogWrite(c_pot2Pin, value);
}
