#define DEBUG 1

#include <Arduino.h>
#include "switch.h"
#include "led.h"
#include "memory.h"

TemporarySwitch sw0(21, 500);
Led led0(20);

Memory mem0(1);

uint8_t state = 0;

void setup() 
{
    Serial.begin(31250);
    sw0.tempSwitchSetup();
    led0.ledSetup();
    mem0.memorySetup();
    
    state = mem0.readBypassState();
    led0.ledSetState(state);
}

void loop() 
{
    sw0.tempSwitchPoll();

    if (sw0.tempSwitchPushed())
    {
        state = !state;
        led0.ledSetState(state);
        mem0.writeBypassState(state);
    }
}