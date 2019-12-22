#include <Arduino.h>
#include <SPI.h>

#include "potentiometer.h"
#include "tap.h"
#include "selector.h"
#include "bypass.h"
#include "memory.h"

Memory mem0;
Bypass bypass0;
Tap tap0;
Selector selector0;

Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2); 

// Selector interrupt function
void selectorInterrupt()
{
  if (bypass0.getBypassState() == 1)
  {
    selector0.selectorMove();

    Serial.println(selector0.getCounter());
  }
}

// Bypass Interupt function
void bypassInterrupt()
{
  if (bypass0.bypassPressed())
  {
    bypass0.switchRelay();
    mem0.writeBypassState(bypass0.getBypassState());
  }
}

void setup()
{
  Serial.begin(9600);
  mem0.memorySetup();

  bypass0.setBypassState(mem0.readBypassState());
  bypass0.bypassSetup();
  attachInterrupt(digitalPinToInterrupt(2), bypassInterrupt, FALLING);
  
  tap0.tapSetup();
  
  selector0.setCounter(mem0.readCurrentPreset());
  selector0.setPresetMode(mem0.readPresetMode());

  selector0.selectorSetup();
  attachInterrupt(digitalPinToInterrupt(10), selectorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), selectorInterrupt, CHANGE);
  selector0.lightSelectorLed();

  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();
}

void loop()
{
  selector0.m_now = millis();
  if(selector0.selectorSwitch())
  {
    selector0.switchPresetMode();
    mem0.writePresetMode(selector0.getPresetMode());
    selector0.setCounter(0);
    selector0.m_newProgram = true;
  }

  if (selector0.m_newProgram)
  {
    selector0.lightSelectorLed();
    mem0.writeCurrentPreset(selector0.getCounter());
    selector0.m_newProgram = false;
  }

  tap0.m_now = millis();
  if (tap0.getInterval() > 0)
  {
    tap0.blinkTapLed();
  }

  if (tap0.tapTimeout())
  {
    tap0.tapReset();
  }

  if (tap0.tapPressed())
  {
    tap0.setTapCount();
  }
  
  if (tap0.divPressed())
  {
    tap0.setDivision();
  }

  if (tap0.m_newInterval || tap0.m_newDivInterval)
  {
    tap0.calculateInterval();
  }

  if (pot0.potTurned())
  {
  }
  if (pot1.potTurned())
  {
  }
  if (pot2.potTurned())
  {
  }
}
