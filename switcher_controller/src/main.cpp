#include <Arduino.h>
#include "memory.h"
#include "led.h"

Memory eeprom0(36);
Led editSwitchLed(31);

void setup()
{
  Serial.begin(115200);
  editSwitchLed.ledSetup();
  eeprom0.memorySetup();
  editSwitchLed.ledTurnOn();
}

void loop()
{
}