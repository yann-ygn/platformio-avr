#include <Arduino.h>
#include "memory.h"
#include "led.h"
#include "preset.h"
#include "display.h"

Memory eeprom0(36);
Led editSwitchLed(31);

Loops looptest(6);
Preset presetTest(65, 1, &looptest);

Loops looptest2(6);
Preset presetTest2(65, 1, &looptest2);

Display displayTest(128, 64, 9, 7, 1);

void setup()
{
  Serial.begin(115200);
  editSwitchLed.ledSetup();
  eeprom0.memorySetup();
  editSwitchLed.ledTurnOn();
  displayTest.displaySetup();
  displayTest.clear();
  displayTest.printMenuHeader("Test");
  displayTest.printNewLine();
  displayTest.printFullScreenChar(65);
  displayTest.display();

  presetTest.getLoops()->setLoopState(1, 1);
  presetTest.getLoops()->setLoopState(4, 1);

  eeprom0.writePreset(presetTest.getBank(), presetTest.getPreset(), presetTest.getLoops()->getLoops(), presetTest.getLoops()->getStates(), presetTest.getLoops()->getCount());
  eeprom0.readPreset(presetTest2.getBank(), presetTest2.getPreset(), presetTest2.getLoops()->getLoops(), presetTest2.getLoops()->getStates(), presetTest2.getLoops()->getCount());
}

void loop()
{
}