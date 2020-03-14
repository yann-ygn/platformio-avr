#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>

#include "FV1.h"

void FV1::FV1Setup()
{
    pinMode(c_pot0Pin, OUTPUT);
    pinMode(c_pot1Pin, OUTPUT);
    pinMode(c_pot2Pin, OUTPUT);

    analogWrite(c_pot0Pin, 0);
    analogWrite(c_pot1Pin, 0);
    analogWrite(c_pot2Pin, 0);
}

void FV1::sendProgramChange(uint8_t program)
{

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
