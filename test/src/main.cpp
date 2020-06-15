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
    eeprom0.writeByte(0, 1);
    Serial.println(eeprom0.readByte(0));

    delay(500);

    eeprom0.writeByte(0, 0);
    Serial.println(eeprom0.readByte(0));

    delay(500);
}