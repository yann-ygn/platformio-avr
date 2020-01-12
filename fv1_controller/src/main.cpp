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
#include "expression.h"

Memory mem0;
Bypass bypass0;
Tap tap0;
Selector selector0;
FV1 dsp0;
Midi midi0;
Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2);
Pot pot3(A3);
DigitalPot dpot0(1);
Expr expr0(A4, 0);

void setup()
{
  midi0.midiSetup();
  mem0.memorySetup();
  //mem0.memoryInitialization();

  midi0.setMidiChannel(mem0.readMidiChannel());

  bypass0.setBypassState(mem0.readBypassState());
  bypass0.bypassSetup();
  attachInterrupt(digitalPinToInterrupt(2), bypassInterrupt, FALLING);

  dsp0.FV1Setup();
  
  tap0.tapSetup();
  
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();
  pot3.potSetup();

  dpot0.digitalPotSetup();

  expr0.exprSetup();

  selector0.selectorSetup();
  attachInterrupt(digitalPinToInterrupt(10), selectorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), selectorInterrupt, CHANGE);

  if (mem0.readPresetMode() == 1) // preset mode
  {
    selector0.setPresetMode(1);
    selector0.setCounter(mem0.readCurrentPreset());
  }
  else // program mode, load the stored program and send it to the DSP
  {
    selector0.setPresetMode(0);
    selector0.setCounter(mem0.readCurrentPreset());

    dsp0.sendProgramChange(selector0.getCounter());
    selector0.lightSelectorLed();

    if (programs[selector0.getCounter()].m_delayEffect == 1) // Stored program is a delay, set the max interval
    {
      tap0.setMaxInterval(programs[selector0.getCounter()].m_maxInterval);
      tap0.setMinInterval(programs[selector0.getCounter()].m_minInterval);

      if (programs[selector0.getCounter()].m_tapEnabled == 1) // Tap is available, check if it was being used
      {
        tap0.setTapState(mem0.readTapState());

        if (tap0.getTapState() == 1) // Tap was used, load the stored values
        {          
          tap0.setInterval(mem0.readIntervalValue());
          tap0.setDivState(mem0.readDivState());

          if (tap0.getDivState() == 1) // Div was active, load the stored value, sends it to the DSP and light the div LED
          {            
            tap0.setDivValue(mem0.readDivValue());
            tap0.setDivInterval(mem0.readDivIntervalValue());
            tap0.lightDivLed();

            dsp0.sendPot0Value(tap0.getMappedDivInterval());
          }
          else // No division set, send the tap interval to the DSP
          {
            dsp0.sendPot0Value(tap0.getMappedInterval());
          }
        }
        else // Tap wasn't being used, send the pot0 current value to the DSP
        {
          dsp0.sendPot0Value(pot0.getMappedPotValue());
        }
      }
      else // Tap is not available, send the pot0 current value to the dsp
      {
        dsp0.sendPot0Value(pot0.getMappedPotValue());
      }
    }
    else // not a delay effect, send the pot0 current value to the dsp
    {
      dsp0.sendPot0Value(pot0.getMappedPotValue());
    }

    // Read and send the value for the other pots to the DSP
    dsp0.sendPot1Value(pot1.getMappedPotValue());
    dsp0.sendPot2Value(pot2.getMappedPotValue());

    // Read the mix pot value and send it to the digital pot
    dpot0.setPotValue(pot3.getMappedPotValue());
  } 
}

void loop()
{
  selector0.m_now = millis();
  
  if(selector0.selectorSwitch()) // Preset / Program switch
  {
    selector0.switchPresetMode();
    mem0.writePresetMode(selector0.getPresetMode());
    selector0.setCounter(0);
    selector0.m_newProgram = true;
  }

  if (selector0.getPresetMode() == 1) // The pedal is in preset mode
  {
    
  }
  
  else // The pedal is in program mode
  {
    if (selector0.m_newProgram) // New program selected send it to the DSP and store it
    {
      selector0.lightSelectorLed();
      dsp0.sendProgramChange(selector0.getCounter());
      mem0.writeCurrentPreset(selector0.getCounter());
      
      if (programs[selector0.getCounter()].m_delayEffect == 1) // If it's a delay effect set the max interval
      {
        tap0.setMaxInterval(programs[selector0.getCounter()].m_maxInterval);
        tap0.setMinInterval(programs[selector0.getCounter()].m_minInterval);

        if (programs[selector0.getCounter()].m_tapEnabled == 1) // New program has tap available
        {
          if (tap0.getTapState() == 1) // Tap was active, send the current interval to the DSP
          {
            if (tap0.getDivState() == 1) // Div was active, load the stored value, sends it to the DSP and light the div LED
            {
              tap0.lightDivLed();

              dsp0.sendPot0Value(tap0.getMappedDivInterval());
            }
            else // No division set, send the tap interval to the DSP
            {
              dsp0.sendPot0Value(tap0.getMappedInterval());
            }
          }
          else // Tap not active, send the current pot0 value to the DSP
          {
            dsp0.sendPot0Value(pot0.getMappedPotValue());
          }
        }
        else // New program doesn't have tap available
        {
          if (tap0.getTapState() == 1) // Tap was enabled, disable it
          {
            tap0.setTapState(0);
            mem0.writeTapState(0);

            if (tap0.getDivState() == 1) // Same with div
            {
              tap0.setDivState(0);
              tap0.setDivValue(1);
              mem0.writeDivState(0);
              mem0.writeDivValue(1);

              tap0.lightDivLed();
            }
          }

          dsp0.sendPot0Value(pot0.getMappedPotValue());
        }
      }
      else // Not a delay effect, turn off the tap LED and send the pot0 value to the DSP
      {
        tap0.turnOffTapLed();
        dsp0.sendPot0Value(pot0.getMappedPotValue());
      }

      dsp0.sendPot1Value(pot1.getMappedPotValue());
      dsp0.sendPot2Value(pot2.getMappedPotValue());
      selector0.m_newProgram = false;
    }

    if (programs[selector0.getCounter()].m_delayEffect == 1) // Current program is a delay effect
    {
      tap0.m_now = millis();

      if (programs[selector0.getCounter()].m_tapEnabled == 1) // Current program has tap available
      {
        if (tap0.getTapState() == 1) // Tap is used, blink the LED according to the current interval
        {
          tap0.blinkTapLed();
        }
        else // Tap isn't used, blink the LED using the pot0 value
        {
          tap0.blinkTapLed(pot0.getLastPotValue());
        }

        if (tap0.tapTimeout()) // Tap timeout, reset
        {
          tap0.tapReset();
        }

        if (tap0.tapPressed()) // Tap press, set tap tempo count
        {
          tap0.setTapCount();
        }
        
        if (tap0.divPressed()) // Div press, set divider
        {
          tap0.setDivision();
        }

        if (tap0.m_newInterval) // New interval calculation trigger, calculate, write to memory and send to DSP
        {
          tap0.calculateInterval();

          mem0.writeTapState(tap0.getTapState());
          mem0.writeIntervalValue(tap0.getInterval());

          dsp0.sendPot0Value(tap0.getMappedInterval());
        }

        if (tap0.m_newDivInterval)
        {
          tap0.calculateDivInterval();
          tap0.lightDivLed();

          mem0.writeDivState(tap0.getDivState());
          mem0.writeDivValue(tap0.getDivValue());
          mem0.writeDivIntervalValue(tap0.getDivInterval());

          dsp0.sendPot0Value(tap0.getMappedDivInterval());
        }
        
        if (pot0.potTurned())
        {
          if (tap0.getTapState() == 1)
          {
            tap0.setTapState(0);
            mem0.writeTapState(0);
            tap0.setDivState(0);
            tap0.setDivValue(1);
            mem0.writeDivState(0);
            tap0.lightDivLed();
          }
          dsp0.sendPot0Value(pot0.getMappedPotValue());
        }
      }
      else // Current program doesn't have tap available
      {
        if (pot0.potTurned())
        {
          dsp0.sendPot0Value(pot0.getMappedPotValue());
        }

        tap0.blinkTapLed(pot0.getLastPotValue());
      }
    }
    else // Current program is not a delay
    {
      if (pot0.potTurned())
      {
        dsp0.sendPot0Value(pot0.getMappedPotValue());
      }
    }
    
    if (pot1.potTurned())
    {
      dsp0.sendPot1Value(pot1.getMappedPotValue());
    }

    if (pot2.potTurned())
    {
      dsp0.sendPot2Value(pot2.getMappedPotValue());
    }

    if (pot3.potTurned())
    {
      dpot0.setPotValue(pot3.getMappedPotValue());
    }
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