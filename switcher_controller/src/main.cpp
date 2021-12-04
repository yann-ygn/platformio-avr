#include <Arduino.h>
#include "hardware.h"

Hardware hardware;

void setup()
{
  Serial.begin(115200);
  hardware.hardwareSetup();
  hardware.restoreLastState();
}

void loop()
{
}