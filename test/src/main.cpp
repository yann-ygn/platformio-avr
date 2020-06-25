#define DEBUG 1

#include <Arduino.h>

#include "hardware.h"

Hardware hardware;

void setup() 
{
    hardware.hardwareSetup();
    hardware.hardwareInitialization();

    if (hardware.getPresetMode())
    {

    }
    else
    {
        
    }
    
}

void loop() 
{
    hardware.hardwarePoll();

    if (hardware.getBypassSwitchPress())
    {
        hardware.bypassSwitch();
    }
}