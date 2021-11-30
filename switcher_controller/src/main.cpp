#include <Arduino.h>
#include "memory.h""
#include "led.h"

Memory eeprom0(38);
Led editSwitchLed(31);

void setup()
{
  Serial.begin(115200);
  editSwitchLed.ledSetup();
  eeprom0.memorySetup();
  eeprom0.memoryReset();
  editSwitchLed.ledTurnOn();
}

void loop()
{
}