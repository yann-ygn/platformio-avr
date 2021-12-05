#include "hardware.h"

Memory mem(0);
Encoder selector(12, 13);
TemporarySwitch selectorSwitch(14, 1000);
TemporarySwitch editSwitch(11, 1000);
Led editSwitchLed(10);

Preset presetBank[c_maxPresets];
Loops presetLoops[c_maxPresets];

void Hardware::hardwareSetup()
{
  Serial.begin(115200);
  delay(500);
  mem.memorySetup();
  selector.encoderSetup();
  selectorSwitch.tempSwitchSetup();
  editSwitch.tempSwitchSetup();
  editSwitchLed.ledSetup();

  editSwitchLed.ledTurnOn();
}

void Hardware::hardwarePoll()
{
    selectorSwitch.tempSwitchPoll();
    editSwitch.tempSwitchPoll();
    selector.encoderPoll();
}

void Hardware::hardwareStartup()
{
    selectorSwitch.tempSwitchPoll();
    editSwitch.tempSwitchPoll();
}

void Hardware::restoreLastState()
{
    m_currentPresetBank = mem.readCurrentPresetBank();
    m_currentPreset = mem.readCurrentPreset();
    loadPresetBank();
    p_currentPreset = &presetBank[m_currentPreset];
}

void Hardware::resetHardwareTriggers()
{

}

void Hardware::loadPresetBank()
{
    for (uint8_t i = 0; i < c_maxPresets; i++)
    {
        presetBank[i].presetSetup(m_currentPresetBank, i, &presetLoops[i], c_maxLoops);
        mem.readPreset(presetBank[i].getBank(), presetBank[i].getPreset(), presetBank[i].getLoops(), presetBank[i].getLoopsStates(), c_maxLoops);
    }
}

bool Hardware::getSelectorMove()
{
    return m_selectorMove;
}

bool Hardware::getSelectorwitchPress()
{
    return m_selectorSwitchPress;
}

bool Hardware::getSelectorSwitchLongPress()
{
    return m_selectorSwitchLongPress;
}

bool Hardware::getEditSwitchPress()
{
    return m_editSwitchPress;
}

bool Hardware::getEditSwitchLongPress()
{
    return m_editSwitchLongPress;
}
