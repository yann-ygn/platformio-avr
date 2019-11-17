#include <Arduino.h>

#include "bypass.h"

Bypass Bypass0;

void setup()
{
    Bypass0.bypassSetup();
}

void loop()
{
    Bypass0.m_now = millis();

    if (Bypass0.bypassPressed())
    {
        Bypass0.switchRelay();
    }
}