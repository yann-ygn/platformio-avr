#include <Arduino.h>
#include "menu.h"
#include "encoder.h"
#include "led.h"
#include "switch.h"
#include "loops.h"

extern MenuItem mainMenu[];
extern MenuItem loopSubMenu[];
extern MenuItem subMenu1[];

bool swTrigger = false;

Encoder encoder0(32, 33);
Led swLed0(31);
TemporarySwitch encSwitch0(34, 1000);
Loops loops(6);

MenuItem mainMenu[] =
{
  MenuItemHeader("MAIN MENU"),
  MenuItem("Test 2"),
  MenuItemSubMenu("Loops settings", loopSubMenu),
  MenuItemSubMenu("Sub Menu 1", subMenu1),
  MenuItem("Test 4"),
  MenuItem("Test 5"),
  MenuItem("Test 6"),
  MenuItem("Test 7"),
  MenuItem("Test 8"),
  MenuItem("Test 9"),
  MenuItemFooter()
};

MenuItem loopSubMenu[] =
{
  MenuItemListIntToggleHeader("LOOPS SETUP"),
  MenuItemListIntToggle(loops.getLoops(), loops.getStates(), loops.getCount()),
  MenuItem(),
  MenuItem(),
  MenuItem(),
  MenuItem(),
  MenuItemSubMenuBack("BACK", mainMenu),
  MenuItemFooter()
};

MenuItem subMenu1[] =
{
  MenuItemSubMenuHeader("SUB MENU 1"),
  MenuItem("Sub Menu Test 1"),
  MenuItem("Sub Menu Test 2"),
  MenuItem("Sub Menu Test 3"),
  MenuItem("Sub Menu Test 4"),
  MenuItemSubMenuBack("BACK", mainMenu),
  MenuItemFooter()
};

Menu menu(128, 64, 7, 9, 2);

void setup()
{
  Serial.begin(115200);
  encoder0.encoderSetup();
  swLed0.ledSetup();
  encSwitch0.tempSwitchSetup();
  loops.LoopsSetup();
  loops.setLoopState(1, 1);
  loops.setLoopState(5, 1);
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