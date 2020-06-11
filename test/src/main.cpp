#include <Arduino.h>

#include "footswitch.h"

Footswitch fsw0(2, 1000);

void setup() 
{
    fsw0.footswitchSetup();
    Serial.begin(9600);
}

void loop() 
{
    fsw0.footswitchPoll();
}