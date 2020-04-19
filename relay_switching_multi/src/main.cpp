#include <Arduino.h>

#include "bypass.h"
#include "settings.h"

Bypass Bypass0(9, 1, 1, 8, 0);
Bypass Bypass1(10, 6, 7, 8, 5);
Settings Settings0;

void setup()
{
    Settings0.modeSetup();
    Bypass0.bypassSetup();
    Bypass1.bypassSetup();

    if (Settings0.getStartupState())
    {
        Bypass0.switchRelay();
    }
}

void loop()
{

}
