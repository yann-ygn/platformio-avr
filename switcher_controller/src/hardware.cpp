#include "hardware.h"
#include "menu.h"
#include "encoder.h"
#include "led.h"
#include "switch.h"
#include "loops.h"

Encoder selector(32, 33);
TemporarySwitch selectorSwitch(34, 1000);
TemporarySwitch editSwitch(30, 1000);
Led editSwitchLed(31);
Loops loops(6);

void Hardware::hardwareSetup()
{
  Serial.begin(115200);
  selector.encoderSetup();
  selectorSwitch.tempSwitchSetup();
  editSwitch.tempSwitchSetup();
  editSwitchLed.ledSetup();
}

void Hardware::hardwarePoll()
{

}

void Hardware::resetHardwareTriggers()
{

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