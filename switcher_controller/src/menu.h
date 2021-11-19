#include <Arduino.h>

#ifndef MENU_H
#define MENU_H

const uint8_t menuItemNone = 0;
const uint8_t menuItemHeader = 1;
const uint8_t menuItemFooter = 2;


class MenuItem
{
    private:
        const char * m_text = NULL;
        uint8_t m_type = menuItemNone;

    public:
        MenuItem(const char * text) : m_text(text) {}
        MenuItem(const char * text, uint8_t type) : m_text(text), m_type(type) {}
};

#endif