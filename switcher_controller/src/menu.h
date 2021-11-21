#include <Arduino.h>
#include "display.h"

#ifndef MENU_H
#define MENU_H

const uint8_t c_menuItemNone = 0;
const uint8_t c_menuItemHeader = 1;
const uint8_t c_menuItemFooter = 2;
const uint8_t c_menuItemSubMenu = 3;

class MenuItem
{
    private:
        const char* m_text = NULL;
        uint8_t m_type = c_menuItemNone;
        MenuItem* m_parentMenu = NULL;

    public:
        MenuItem(const char* text) : m_text(text) {}
        MenuItem(const char* text, uint8_t type) : m_text(text), m_type(type) {}
        MenuItem(const char* text, uint8_t type, MenuItem* parent) : m_text(text), m_type(type), m_parentMenu(parent) {}

        const char* getText();

        uint8_t getType();

        MenuItem* getParentMenu();
};

class MenuItemHeader : public MenuItem
{
    public:
        MenuItemHeader(const char* text) : MenuItem(text, c_menuItemHeader) {}
        MenuItemHeader(const char* text, MenuItem* parent) : MenuItem(text, c_menuItemHeader, parent) {}
};

class MenuItemFooter : public MenuItem
{
    public:
        MenuItemFooter() : MenuItem(NULL, c_menuItemFooter) {}
};

class MenuItemSubMenu : public MenuItem
{
    public:
        MenuItemSubMenu(const char* text, MenuItem* parent) : MenuItem(text, c_menuItemSubMenu, parent) {}
};

class Menu
{
    private:
        Display m_display;
        MenuItem* m_currentMenuArray = NULL;
        uint8_t m_menuMaxLines;
        uint8_t m_menuTopItem = 0;
        uint8_t m_menuBottomItem;
        uint8_t m_menuCursorPosition = 1; // 0 is always the header

        void drawMenu();
        void drawCursor();
        bool menuTop();
        bool menuBottom();

    public:
        Menu(uint8_t width, uint8_t height, uint8_t lines) :
            m_display(width, height),
            m_menuMaxLines(lines),
            m_menuBottomItem(lines - 1) {}

        void menuSetup(MenuItem* menu);
        void displayMenu();
};

#endif