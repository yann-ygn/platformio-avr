#include <Arduino.h>
#include <SPI.h>

#include "potentiometer.h"
#include "tap.h"
#include "selector.h"
#include "bypass.h"

/*
Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2);

Tap tap0;
Selector selector0;
Bypass bypass0;

void selectorRotate()
{
  selector0.selectorMove();
}
*/

void setup()
{
  /*
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();

  bypass0.bypassSetup();

  tap0.tapSetup();
  selector0.selectorSetup();

  attachInterrupt(digitalPinToInterrupt(10), selectorRotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(11), selectorRotate, CHANGE);
  */

  Serial.begin(9600);
}

void loop()
{
  /*
  bypass0.m_now = millis();

  if (bypass0.bypassPressed())
  {
      bypass0.switchRelay();
  }

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
      Serial.println(tap0.getDivision());
      Serial.println("Interval : ");
      Serial.println(tap0.getDivInterval());
    }
  }
  
  if (selector0.m_newProgram)
  {
    selector0.lightSelectorLed();
    Serial.println(selector0.m_counter);
    selector0.m_newProgram = false;
  }

  selector0.m_now = millis();
  if(selector0.presetSwitch())
  {
    selector0.setPresetMode();
    Serial.println(selector0.m_presetMode);
  }
  
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
  }
  */
}
