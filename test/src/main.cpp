#define DEBUG 1

#include <Arduino.h>

#include "switch.h"
#include "leddriver.h"
#include "eeprom.h"
#include "encoder.h"

Encoder encoder0(2, 3, 0, 7);
TemporarySwitch encoder0Switch(4, 1000);

void setup() 
{
    Serial.begin(9600);
    encoder0.encoderSetup();
    encoder0Switch.tempSwitchSetup();
}

void loop() 
{
    encoder0.encoderMove();
    encoder0Switch.tempSwitchPoll();
}