#include <Arduino.h>
#include "menu.h"

Menu menu(128, 64, 7);
MenuItem mainMenu[] =
{
  MenuItemHeader("MAIN MENU"),
  MenuItem("Test 1"),
  MenuItem("Test 2"),
  MenuItemSubMenu("Test Sub Menu", mainMenu),
  MenuItemFooter()
};

void setup()
{
  Serial.begin(115200);
  menu.menuSetup(mainMenu);
  menu.displayMenu();
}

void loop()
{

}