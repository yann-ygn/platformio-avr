#include <Arduino.h>
#include <Wire.h>
#include <display.h>

Display test(&Wire, 128, 64);

void setup()
{
  Serial.begin(115200);
  test.displaySetup();
  delay(2000);
  test.clear();
  test.printMenuHeader("MAIN MENU");
  test.printMenuItem("Item 1");
  test.printMenuItem("Item 2");
  test.printMenuItem("Item 3");
  test.printMenuItem("Item 4");
  test.printMenuItem("Item 5");
  test.printMenuItem("Item 6");
  test.display();
}

void loop()
{

}