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
    
    if (fsw0.footswitchSwitched())
    {
        Serial.println("Switched");
    }
    if (fsw0.footswitchPushed())
    {
        Serial.println("Pushed");
    }
    if (fsw0.footswitchReleased())
    {
        Serial.println("Released");
    }
    if(fsw0.footswitchLongPress())
    {
        Serial.println("Long Press");
    }
}