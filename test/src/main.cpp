#define DEBUG 1

#include <Arduino.h>

#include "hardware.h"

Hardware hardware;

void setup() 
{
    hardware.hardwareSetup();
    hardware.hardwareInitialization();
    hardware.restoreLastState();
}

void loop() 
{
    hardware.hardwarePoll(); // Poll the moving parts
    
    if (hardware.getBypassSwitchPress()) // Bypass switch Press
    {
        hardware.bypassSwitch(); // Turn the pedal on/off
    }
    
    if (hardware.getBypassState()) // Is the pedal on
    {
        if (hardware.getSelectorSwitchPress()) // Selector switch long press
        {
            hardware.presetModeSwitch(); // Switch the preset/program mode
        }
        
        if (hardware.getPresetMode()) // Preset mode active
        {
            if (hardware.getSelectorMove()) // The selector moved
            {
                hardware.loadPreset(); // Load the selected preset
            }
        }
        else // Program mode active
        {
            if (hardware.getSelectorMove()) // The selector moved
            {
                hardware.loadProgram(); // Load the selected program
            }
        }
    }

    hardware.resetTriggers();
}