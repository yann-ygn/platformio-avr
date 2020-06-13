#include <Arduino.h>

#include "footswitch.h"
#include "leddriver.h"

LedDriver16 test(2);

void setup() 
{
    Serial.begin(9600);

    test.ledDriverSetup();
}

void loop() 
{
    
}