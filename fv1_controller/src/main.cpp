#include <Arduino.h>
#include <SPI.h>


//#include "potentiometer.h"
//#include "tap.h"
//#include "selector.h"
//#include "bypass.h"
#include "memory.h"


Memory mem0;

//Bypass bypass0;

/*
Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2); 

Tap tap0;
Selector selector0;

// Selector interrupt function
void selectorInterrupt()
{
  if (bypass0.getBypassState() == 1)
  {
    selector0.selectorMove();

    if (selector0.m_newProgram)
    {
      if (selector0.getPresetMode() == 0)
      {
        selector0.lightSelectorLed();
        Serial.println(selector0.getCounter());
        selector0.m_newProgram = false;

        // TODO : change program
      }
      else
      {
        selector0.lightSelectorLed();
        Serial.println(selector0.getCounter());
        selector0.m_newProgram = false;

        // TODO : change the preset
      }
    }
  }
}

// Bypass Interupt function
void bypassInterrupt()
{
  if (bypass0.bypassPressed())
  {
    bypass0.switchRelay();
    mem0.writeBypassState(bypass0.getBypassState());

    Serial.println(mem0.readBypassState());
  }
}
*/


void setup()
{
  /*
  mem0.memorySetup();

  bypass0.setBypassState(mem0.readBypassState());
  bypass0.bypassSetup();
  attachInterrupt(digitalPinToInterrupt(2), bypassInterrupt, FALLING);

  selector0.selectorSetup();
  attachInterrupt(digitalPinToInterrupt(10), selectorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), selectorInterrupt, CHANGE);
  
  tap0.tapSetup();

  
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();
  */

  mem0.memorySetup();

  Serial.begin(9600);
}

void loop()
{
  /*
  tap0.m_now = millis();
  tap0.blinkTapLed();
  if (tap0.tapTimeout())
  {
    tap0.tapReset();
    Serial.println("Reset");
  }

  if (tap0.tapPressed())
  {
    Serial.println("Tap count : ");
    tap0.setTapCount();
    Serial.println(tap0.getTapCount());
    Serial.println(tap0.m_now);
        
    if (tap0.getTapCount() == tap0.c_maxTaps)
    {
      tap0.setInterval();
      Serial.println("Interval : ");
      Serial.println(tap0.getInterval());
    }
  }
  
  if (tap0.divPressed())
  {
    Serial.println("Long press");
    tap0.setDivision();

    if (tap0.m_newInterval)
    {
      tap0.setDivInterval();
      tap0.lightDivLed();
      Serial.println("Division : ");
      Serial.println(tap0.getDivValue());
      Serial.println("Interval : ");
      Serial.println(tap0.getDivInterval());
    }
  }

  selector0.m_now = millis();
  if(selector0.presetSwitch())
  {
    selector0.setPresetMode();
    Serial.println(selector0.getPresetMode());
  }
  /*
  if (pot0.potTurned())
  {
    Serial.println(pot0.getPotValue());
  }
  if (pot1.potTurned())
  {
    Serial.println(pot1.getPotValue());
  }
  if (pot2.potTurned())
  {
    Serial.println(pot2.getPotValue());
  }*/

  Serial.println(mem0.readBypassState());
  mem0.writeBypassState(0);

  delay(500);

  Serial.println(mem0.readBypassState());
  mem0.writeBypassState(1);

  delay(500);
}
