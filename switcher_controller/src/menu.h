#include <Arduino.h>
#include "display.h"

#ifndef MENU_H
#define MENU_H

const uint8_t c_menuItemTypeNone = 0;
const uint8_t c_menuItemTypeMainMenuHeader = 1;
const uint8_t c_menuItemTypeSubMenuHeader = 2;
const uint8_t c_menuItemTypeFooter = 3;
const uint8_t c_menuItemTypeSubMenu = 4;
const uint8_t c_menuItemTypeSubMenuBack = 5;

class MenuItem
{
    private:
        const char* m_menuItemText = NULL;
        uint8_t m_menuItemType = c_menuItemTypeNone;
        MenuItem* m_menuItemSubMenu = NULL;

    public:
        MenuItem(const char* text) : m_menuItemText(text) {}
        MenuItem(const char* text, uint8_t type) : m_menuItemText(text), m_menuItemType(type) {}
        MenuItem(const char* text, uint8_t type, MenuItem* submenu) : m_menuItemText(text), m_menuItemType(type), m_menuItemSubMenu(submenu) {}

        const char* getMenuItemText();

        uint8_t getMenuItemType();

        MenuItem* getMenuItemSubMenu();
};

class MenuItemHeader : public MenuItem
{
    public:
        MenuItemHeader(const char* text) : MenuItem(text, c_menuItemTypeMainMenuHeader) {} // Main menu header
        MenuItemHeader(const char* text, MenuItem* submenu) : MenuItem(text, c_menuItemTypeSubMenuHeader, submenu) {} // Sub menu header
};

class MenuItemFooter : public MenuItem
{
    public:
        MenuItemFooter() : MenuItem(NULL, c_menuItemTypeFooter) {}
};

class MenuItemSubMenu : public MenuItem
{
    public:
        MenuItemSubMenu(const char* text, MenuItem* submenu) : MenuItem(text, c_menuItemTypeSubMenu, submenu) {}
};

class MenuItemSubMenuBack : public MenuItem
{
    public:
        MenuItemSubMenuBack(const char* text) : MenuItem(text, c_menuItemTypeSubMenuBack) {}
};

class Menu
{
    private:
        Display m_display;
        MenuItem* m_currentMenuArray = NULL;
        uint8_t m_menuMaxLines;
        uint8_t m_menuTopItem = 1;
        uint8_t m_menuPreviousTopItem = 1;
        uint8_t m_menuBottomItem;
        uint8_t m_menuPreviousBottomItem = 0;
        uint8_t m_menuCursorPosition = 1; // 0 is always the header
        uint8_t m_menuPreviousCursorPosition = 1;

        void drawMenu();
        void drawCursor();
        void displayMenu();
        void resetMenu(bool history);
        bool menuTop();
        bool menuBottom();

    public:
        Menu(uint8_t width, uint8_t height, uint8_t maxlines, uint8_t newline, uint8_t headeroffset) :
            m_display(width, height, newline, maxlines, headeroffset),
            m_menuMaxLines(maxlines),
            m_menuBottomItem(maxlines - 1) {}

        void menuSetup(MenuItem* menu);
        void menuCursorUp();
        void menuCursorDown();
        void menuCursorEnter();
};

#endif