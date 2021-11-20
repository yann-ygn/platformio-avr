#include <Arduino.h>

#ifndef MENU_H
#define MENU_H

const uint8_t menuItemNone = 0;
const uint8_t menuItemHeader = 1;
const uint8_t menuItemFooter = 2;

class MenuItem
{
    private:
        const char* m_text = NULL;
        uint8_t m_type = menuItemNone;
        MenuItem* m_parentMenu = NULL;

    public:
        MenuItem(const char* text) : m_text(text) {}
        MenuItem(const char* text, uint8_t type) : m_text(text), m_type(type) {}
        MenuItem(const char* text, uint8_t type, MenuItem* parent) : m_text(text), m_type(type), m_parentMenu(parent) {}

        const char * getText();

        uint8_t getType();

        MenuItem * getParentMenu();
};

class MenuItemHeader : public MenuItem
{
    MenuItemHeader(const char* text) : MenuItem(text, menuItemHeader) {}
    MenuItemHeader(const char* text, MenuItem* parent) : MenuItem(text, menuItemHeader, parent) {}
};

class MenuItemFooter : public MenuItem
{
    MenuItemFooter() : MenuItem(NULL, menuItemFooter) {}
};

class Menu
{
    private:

    public:
};

#endif