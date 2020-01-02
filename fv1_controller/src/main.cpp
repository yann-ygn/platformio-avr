#include <Arduino.h>
#include <SPI.h>

#include "potentiometer.h"
#include "tap.h"
#include "selector.h"
#include "bypass.h"
#include "memory.h"
#include "program.h"
#include "FV1.h"
#include "midi.h"

Memory mem0;
Bypass bypass0;
Tap tap0;
Selector selector0;
FV1 dsp0;
Midi midi0;

Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2);

program test = programs[0];

// Selector interrupt function
void selectorInterrupt()
{
  if (bypass0.getBypassState() == 1)
  {
    selector0.selectorMove();
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

void midiHandler(uint8_t message, uint8_t byte1, uint8_t byte2)
{

}

void setup()
{
  midi0.midiSetup();
  mem0.memorySetup();

  if (mem0.readInitialSetupState() == 0) // First startup, need to initialize
  {
    mem0.writeBypassState(0);
    mem0.writePresetMode(0);
    mem0.writeCurrentPreset(0);
    mem0.writeTapState(0);
    mem0.writeDivState(0);
    mem0.writeDivValue(0);
    mem0.writeDivIntervalValue(0);
    mem0.writeIntervalValue(0);

    mem0.writeInitialSetupState(1); // Initialization done
  }

  bypass0.setBypassState(mem0.readBypassState());
  bypass0.bypassSetup();
  attachInterrupt(digitalPinToInterrupt(2), bypassInterrupt, FALLING);

  dsp0.FV1Setup();
  
  tap0.tapSetup();
  
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();

  selector0.selectorSetup();
  attachInterrupt(digitalPinToInterrupt(10), selectorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), selectorInterrupt, CHANGE);

  if (mem0.readPresetMode() == 1) // preset mode
  {
    selector0.setPresetMode(mem0.readPresetMode());
    selector0.setCounter(mem0.readCurrentPreset());
  }
  else // program mode
  {
    selector0.setPresetMode(mem0.readPresetMode());
    selector0.setCounter(mem0.readCurrentPreset());
  } 

  dsp0.sendProgramChange(selector0.getCounter());
  selector0.lightSelectorLed();
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
    dsp0.sendProgramChange(selector0.getCounter());
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
    dsp0.sendPot0Value(pot0.getPotValue());
  }

  if (pot1.potTurned())
  {
    dsp0.sendPot1Value(pot1.getPotValue());
  }

  if (pot2.potTurned())
  {
    dsp0.sendPot2Value(pot2.getPotValue());
  }

  if (midi0.completeMidiMessage())
  {
    midiHandler(midi0.getCommandCode(), midi0.getDataByte1(), midi0.getDataByte2());
    midi0.resetMidiMessage();
  }
}
