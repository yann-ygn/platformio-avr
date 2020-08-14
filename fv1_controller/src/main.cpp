#define DEBUG 1

#include <Arduino.h>

#include "hardware.h"

Hardware hardware;

uint8_t test = 0;


void setup() 
{
    hardware.hardwareSetup();
    delay(500);
    hardware.hardwareInitialization();
    hardware.restoreLastState();
    delay(500);
    hardware.hardwareStartup();
    test == 1;
}

void loop() 
{
    hardware.hardwarePoll(); // Poll the moving parts
    
    if (hardware.getBypassState()) // The pedal is on
    {
        hardware.blinkTapLed();

        if (hardware.getSelectorSwitchReleased()) // Selector switch press
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
            if (hardware.getSelectorSwitchLongPress()) // Selector switch long press
            {
                hardware.savePreset(); // Save the current program and parameters as a preset
            }

            if (hardware.getSelectorMove()) // The selector moved
            {
                hardware.loadProgram(); // Load the selected program
            }

            if (hardware.getTapSwitchPress()) // Tap switch press
            {
                hardware.processTap(); // Process it
            }

            if(hardware.getTapSwitchLongPress()) // Tap switch long press
            {
                hardware.processDiv(); // Process it
            }

            if (hardware.getPot0Turned()) // Pot0 moved
            {
                hardware.processPot0(); // Process it
            }

            if (hardware.getPot1Turned()) // Pot1 moved
            {
                hardware.processPot1(); // Process it
            }

            if (hardware.getPot2Turned()) // Pot2 moved
            {
                hardware.processPot2(); // Process it
            }

            if (hardware.getPot3Turned()) // Pot3 moved
            {
                hardware.processPot3(); // Process it
            }
        }
    }
    
    if (hardware.getBypassSwitchPress()) // Bypass switch Press
    {
        hardware.bypassSwitch(); // Turn the pedal on/off
    }

    hardware.resetTriggers();
}