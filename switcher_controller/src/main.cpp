#include <Arduino.h>
#include "hardware.h"

Hardware hardware;

void setup()
{
  Serial.begin(115200);
  hardware.hardwareSetup();
  hardware.restoreLastState();
  hardware.menuSetup();
}

void loop()
{
  hardware.hardwarePoll();

  if (hardware.getPresetMenuDisplay())
  {
    if (hardware.getEditSwitchPress())
    {
      
    }
  }
  hardware.resetHardwareTriggers();
}