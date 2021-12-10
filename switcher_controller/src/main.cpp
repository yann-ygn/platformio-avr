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

    if (hardware.getPresetUpFswPress() || hardware.getPresetDownFswPress())
    {
      hardware.loadPresetBank();
    }

    if (hardware.getPreset0FswPress() || hardware.getPreset1FswPress() ||
        hardware.getPreset2FswPress() || hardware.getPreset3FswPress())
    {
      hardware.loadPreset();
    }
  }

  hardware.resetHardwareTriggers();
}