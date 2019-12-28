#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "FV1.h"

void FV1::FV1Setup()
{
    pinMode(c_latchPin, OUTPUT);
    pinMode(c_pot0Pin, OUTPUT);
    pinMode(c_pot1Pin, OUTPUT);
    pinMode(c_pot2Pin, OUTPUT);

    digitalWrite(c_latchPin, HIGH);

    SPI.begin();
    sendProgramChange(0);

    analogWrite(c_pot0Pin, 0);
    analogWrite(c_pot1Pin, 0);
    analogWrite(c_pot2Pin, 0);
}

void FV1::sendProgramChange(uint8_t program)
{
    SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
    digitalWrite(c_latchPin, LOW);
    SPI.transfer(program);
    digitalWrite(c_latchPin, HIGH);
    SPI.endTransaction();
}

void FV1::sendPot0Value(int value)
{
    analogWrite(c_pot0Pin, map(value, 0, 1024, 0, 255));
}

void FV1::sendPot1Value(int value)
{
    analogWrite(c_pot1Pin, map(value, 0, 1024, 0, 255));
}

void FV1::sendPot2Value(int value)
{
    analogWrite(c_pot2Pin, map(value, 0, 1024, 0, 255));
}
