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
    for (uint8_t i = 0; i < 8; i++)
    {
        test.lightLed2(i);
        delay(500);
        test.lightAllLedOff();
        delay(500);
    }
}