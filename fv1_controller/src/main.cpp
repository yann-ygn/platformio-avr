#include <Arduino.h>
#include <SPI.h>

#include "main.h"
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

void setup()
{
  mem0.memorySetup();

  midi0.midiSetup();
  midi0.setMidiChannel(mem0.readMidiChannel());

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

    if (programs[selector0.getCounter()].m_delayEffect == 1) // Is this program a delay effect
    {
      if (programs[selector0.getCounter()].m_tapEnabled == 1) // If tap is enabled we need to load the stored values
      {
        tap0.setTapState(mem0.readTapState());
        tap0.setInterval(mem0.readIntervalValue());
        tap0.setDivState(mem0.readDivState());
        tap0.setDivValue(mem0.readDivValue());
        tap0.setDivInterval(mem0.readDivIntervalValue());

        if (tap0.getTapState() == 1) // Tap was active, need to check if it was divided
        {
          if (tap0.getDivState() == 1) // Div was active, light the status LED
          {
            tap0.lightDivLed();
          }
        }
        else // Tap wasn't active, send the pot0 current value to the DSP
        {
          /* code */
        }
      }
    }
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

void selectorInterrupt()
{
  if (bypass0.getBypassState() == 1)
  {
    selector0.selectorMove();
  }
}

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