#include <Arduino.h>

#include "potentiometer.h"

Pot pot0(A0);
Pot pot1(A1);
Pot pot2(A2);

void setup()
{
  pot0.potSetup();
  pot1.potSetup();
  pot2.potSetup();
  Serial.begin(9600);
}


void loop()
{
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
}