#include <Arduino.h>
#include "display.h"

#ifndef MENU_H
#define MENU_H

const uint8_t c_menuItemNone = 0;
const uint8_t c_menuItemMainMenuHeader = 1;
const uint8_t c_menuItemSubMenuHeader = 2;
const uint8_t c_menuItemFooter = 3;
const uint8_t c_menuItemSubMenu = 4;
const uint8_t c_menuItemSubMenuBack = 5;

class MenuItem
{
    private:
        const char* m_text = NULL;
        uint8_t m_type = c_menuItemNone;
        MenuItem* m_subMenu = NULL;

    public:
        MenuItem(const char* text) : m_text(text) {}
        MenuItem(const char* text, uint8_t type) : m_text(text), m_type(type) {}
        MenuItem(const char* text, uint8_t type, MenuItem* submenu) : m_text(text), m_type(type), m_subMenu(submenu) {}

        const char* getText();

        uint8_t getType();

        MenuItem* getSubMenu();
};

class MenuItemHeader : public MenuItem
{
    public:
        MenuItemHeader(const char* text) : MenuItem(text, c_menuItemMainMenuHeader) {} // Main menu header
        MenuItemHeader(const char* text, MenuItem* submenu) : MenuItem(text, c_menuItemSubMenuHeader, submenu) {} // Sub menu header
};

class MenuItemFooter : public MenuItem
{
    public:
        MenuItemFooter() : MenuItem(NULL, c_menuItemFooter) {}
};

class MenuItemSubMenu : public MenuItem
{
    public:
        MenuItemSubMenu(const char* text, MenuItem* submenu) : MenuItem(text, c_menuItemSubMenu, submenu) {}
};

class MenuItemSubMenuBack : public MenuItem
{
    public:
        MenuItemSubMenuBack(const char* text) : MenuItem(text, c_menuItemSubMenuBack) {}
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