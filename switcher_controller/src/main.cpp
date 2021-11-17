#include <Arduino.h>
#include <Wire.h>
#include <display.h>

Display test(&Wire, 128, 64);

void setup()
{
  Serial.begin(115200);
  test.displaySetup();
  delay(2000);
  test.printMenuHeader("test");
}

void loop()
{

}