#include <Arduino.h>

#include "potentiometer.h"
#include "tap.h"

//Pot pot0(A0);

Tap tap0;

void setup()
{
  //pot0.potSetup();

  tap0.tapSetup();

  Serial.begin(9600);
}


void loop()
{
  tap0.m_now = millis();
  tap0.blinkTapLed();
  if (tap0.tapTimeout())
  {
    tap0.tapReset();
    Serial.println("Reset");
  }

  if (tap0.tapPressed())
  {
    Serial.println("Tap");
    tap0.setTapCount();
    Serial.println(tap0.getTapCount());
    Serial.println(tap0.m_now);
        
    if (tap0.getTapCount() == tap0.c_maxTaps)
    {
      tap0.setInterval();
      Serial.println(tap0.getInterval());
    }
  }
  
  if (tap0.divPressed())
  {
    Serial.println("Long press");
    tap0.setDivision();

    if (tap0.m_newInterval)
    {
      tap0.setInterval();
      tap0.lightDivLed();
      Serial.println(tap0.getDivision());
    }
  }
}