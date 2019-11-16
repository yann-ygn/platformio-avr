#include <Arduino.h>

#include "bypass.h"

Bypass Switch0(3, 1, 2, 4, 0);

void setup()
{
    Switch0.bypassSetup();
}

void loop()
{
    Switch0.m_now = millis();

    if (Switch0.bypassPressed())
    {
        Switch0.switchRelay();
    }
}