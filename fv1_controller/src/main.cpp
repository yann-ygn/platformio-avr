#include <Arduino.h>

#include "potentiometer.h"
#include "tap.h"
#include "selector.h"

//Pot pot0(A0);

Tap tap0;
Selector selector0;

void selectorRotate()
{
  selector0.selectorMove();
}

void setup()
{
  //pot0.potSetup();

  tap0.tapSetup();
  selector0.selectorSetup();

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(18), selectorRotate, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), selectorRotate, CHANGE);
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
      Serial.println(tap0.getDivision());
      Serial.println("Interval : ");
      Serial.println(tap0.getDivInterval());
    }
  }
  */
  if (selector0.m_newProgram)
  {
    Serial.println(selector0.m_counter);
    selector0.m_newProgram = false;
  }
}
