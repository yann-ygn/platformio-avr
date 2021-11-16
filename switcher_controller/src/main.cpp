#include <Arduino.h>
#include <Wire.h>
#include <display.h>


void setup()
{
  Serial.begin(115200);
  Display test(&Wire, 128, 64);

  delay(2000);
}

void loop()
{

}