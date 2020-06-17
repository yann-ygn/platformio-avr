#define DEBUG 1

#include <Arduino.h>

#include "footswitch.h"
#include "leddriver.h"
#include "eeprom.h"

Eeprom eeprom0(2);

void setup() 
{
    Serial.begin(9600);
    eeprom0.eepromSetup();
}

void loop() 
{
    eeprom0.testArray();
}