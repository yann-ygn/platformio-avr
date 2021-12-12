#include <Arduino.h>
#include "hardware.h"

Hardware hardware;

void setup()
{
  Serial.begin(115200);
  hardware.hardwareSetup();
  delay(500);
  hardware.menuSetup();
  hardware.restoreLastState();
  hardware.hardwareStartup();
  delay(500);
}

void loop()
{
  hardware.hardwarePoll();

  if (hardware.getPresetMenuDisplay())
  {
    if (hardware.getEditSwitchPress())
    {
      hardware.displayPresetEditMenu();
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

  if (hardware.getPresetEditMenuDisplay())
  {
    if (hardware.getSelectorMove())
    {
      hardware.processSelector();
    }

    if (hardware.getSelectorwitchPress())
    {
      hardware.processSelectorSwitch();
    }
  }

  hardware.resetHardwareTriggers();
}