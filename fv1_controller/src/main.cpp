#include <Arduino.h>

#include "potentiometer.h"
#include "tap.h"

Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2);

Tap tap0(13, 14);

void setup()
{
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();

  tap0.tapSetup();

  Serial.begin(9600);
}


void loop()
{
  if (pot0.potTurned())
  {
    Serial.println(pot0.getPotValue());
  }
}