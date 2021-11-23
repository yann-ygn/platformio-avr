#include <Arduino.h>
#include "menu.h"
#include "encoder.h"
#include "led.h"
#include "switch.h"

extern MenuItem mainMenu[];
extern MenuItem subMenu1[];

bool swTrigger = false;

Encoder encoder0(32, 33);
Led swLed0(31);
TemporarySwitch encSwitch0(34, 1000);

MenuItem mainMenu[] =
{
  MenuItemHeader("MAIN MENU"),
  MenuItem("Test 1"),
  MenuItem("Test 2"),
  MenuItemSubMenu("Sub Menu 1", subMenu1),
  MenuItem("Test 4"),
  MenuItem("Test 5"),
  MenuItem("Test 6"),
  MenuItem("Test 7"),
  MenuItem("Test 8"),
  MenuItem("Test 9"),
  MenuItemFooter()
};

MenuItem subMenu1[] =
{
  MenuItemHeader("SUB MENU 1", mainMenu),
  MenuItem("Sub Menu Test 1"),
  MenuItem("Sub Menu Test 2"),
  MenuItem("Sub Menu Test 3"),
  MenuItem("Sub Menu Test 4"),
  MenuItemSubMenuBack("BACK"),
  MenuItemFooter()
};

Menu menu(128, 64, 7);

void setup()
{
  Serial.begin(115200);
  encoder0.encoderSetup();
  swLed0.ledSetup();
  encSwitch0.tempSwitchSetup();
  menu.menuSetup(mainMenu);

  swLed0.ledTurnOn();
}

void loop()
{
  encSwitch0.tempSwitchPoll();

  if (encoder0.encoderPoll())
  {
    if (encoder0.getEncoderState() == c_encoderIncrement)
    {
      Serial.println("UP");
      menu.menuCursorUp();
    }
    else if (encoder0.getEncoderState() == c_encoderDrecrement)
    {
      Serial.println("DOWN");
      menu.menuCursorDown();
    }
  }

  if (encSwitch0.tempSwitchPushed())
  {
    swTrigger = true;
  }

  if (swTrigger)
  {
    menu.menuCursorEnter();
    swTrigger = false;
  }
}