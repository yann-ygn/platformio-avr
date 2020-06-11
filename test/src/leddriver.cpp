#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>
#include "leddriver.h"

void LedDriver8::ledDriverSetup()
{
    pinMode(m_csPin, OUTPUT);
    digitalWrite(m_csPin, HIGH);
}

void LedDriver8::select()
{

}

void LedDriver8::deselect()
{
    
}