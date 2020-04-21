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

    if (Settings0.getSwitchMode() == 0) // On/Off mode
    {
        if (Settings0.getStartupState() == 0) // Starts on
        {
            Bypass0.switchRelay();
            Bypass0.lightActiveLed();

            if (Settings0.getDefaultEffect() == 0) // Sustainer
            {
                Bypass1.switchActiveLed();
                Bypass1.switchRelay();
                Bypass1.lightActiveLed();
            }
            else // Compressor
            {
                Bypass1.lightActiveLed();
            }
        }
    }
    else // Flip flop mode
    {
        if (Settings0.getStartupState() == 0)
        {
            Bypass0.switchRelay();

            if (Settings0.getDefaultEffect() == 0) // Sustainer
            {
                Bypass1.switchRelay();
                Bypass1.lightActiveLed();
            }
            else // Compressor
            {
                Bypass0.lightActiveLed();
            }            
        }
    }
    
}

void loop()
{
    Bypass0.m_now = millis();
    Bypass1.m_now = millis();

    if (Settings0.getSwitchMode() == 0) // On/Off mode
    {
        if (Bypass0.bypassPressed())
        {
            if (Bypass0.getRelayState() == 1) // Effect is on
            {
                if (Bypass1.getRelayState() == 1) //Sustainer is on
                {
                    Bypass1.switchRelay();
                    Bypass1.switchActiveLed();
                }
                
                Bypass1.turnOffLed();
                Bypass0.switchRelay();
                Bypass0.turnOffLed();
            }
            else // Effect is off
            {
                Bypass0.switchRelay();
                Bypass0.lightActiveLed();

                if (Settings0.getDefaultEffect() == 0) // Sustainer
                {
                    Bypass1.switchRelay();
                    Bypass1.switchActiveLed();
                    Bypass1.lightActiveLed();
                }
                else // Compressor
                {
                    Bypass1.lightActiveLed();
                }
            }
        }

        if (Bypass1.bypassPressed() && Bypass0.getRelayState() == 1)
        {
            Bypass1.switchRelay();
            Bypass1.switchActiveLed();
            Bypass1.lightActiveLed();
        }
    }
    else // Flip flop mode
    {
        if (Bypass0.bypassPressed())
        {
            if (Bypass0.getRelayState() == 0) // Nothing on, switch the compressor on
            {
                Bypass0.switchRelay();
                Bypass0.lightActiveLed();
            }
            
            else if (Bypass0.getRelayState() == 1 && Bypass1.getRelayState() == 0) // Compressor on, Switch off
            {
                Bypass0.switchRelay();
                Bypass0.turnOffLed();
            }
            
            if (Bypass0.getRelayState() == 1 && Bypass1.getRelayState() == 1) // Sustainer on, switch to compressor
            {
                Bypass1.switchRelay();
                Bypass1.turnOffLed();
                Bypass0.lightActiveLed();
            }
            
        }

        if (Bypass1.bypassPressed())
        {
            if (Bypass0.getRelayState() == 0) // Nothing on, switch the sustainer on
            {
                Bypass0.switchRelay();
                Bypass1.switchRelay();
                Bypass1.lightActiveLed();
            }

            else if (Bypass0.getRelayState() == 1 && Bypass1.getRelayState() == 1) // Sustainer on, switch off
            {
                Bypass1.switchRelay();
                Bypass0.switchRelay();
                Bypass1.turnOffLed();
            }

            if (Bypass0.getRelayState() == 1 && Bypass1.getRelayState() == 0) // Compressor on, switch to sustainer
            {
                Bypass1.switchRelay();
                Bypass0.turnOffLed();
                Bypass1.lightActiveLed();
            }
        }
    }
}
