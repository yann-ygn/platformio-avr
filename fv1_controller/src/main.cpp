#include <Arduino.h>
#include <SPI.h>

//#include "potentiometer.h"
#include "tap.h"
#include "selector.h"
#include "bypass.h"
#include "memory.h"

Memory mem0;
Bypass bypass0;
Tap tap0;
Selector selector0;

/*
Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2); 
*/

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

    Serial.println(mem0.readBypassState());
  }
}

void setup()
{
  mem0.memorySetup();
  bypass0.setBypassState(mem0.readBypassState());
  bypass0.bypassSetup();
  attachInterrupt(digitalPinToInterrupt(2), bypassInterrupt, FALLING);
  
  tap0.tapSetup();
  
  selector0.selectorSetup();
  attachInterrupt(digitalPinToInterrupt(10), selectorInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), selectorInterrupt, CHANGE);

  /*
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();
  */
  Serial.begin(9600);
}

void loop()
{
  if (bypass0.getBypassState() == 1) // Is the pedal on
  {
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
  }
  else
  {
    
  }
  
  /*
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

  //mem0.memoryTest();
}
