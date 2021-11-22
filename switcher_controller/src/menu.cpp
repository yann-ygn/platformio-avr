#include "menu.h"

const char* MenuItem::getText()
{
    return m_text;
}

uint8_t MenuItem::getType()
{
    return m_type;
}

MenuItem* MenuItem::getParentMenu()
{
    return m_parentMenu;
}

void Menu::drawMenu()
{
    MenuItem* item = &m_currentMenuArray[0]; // 0 is always the header
    m_display.printMenuHeader(item->getText()); // Draw the menu header

    for (uint8_t i = m_menuTopItem; i <= m_menuBottomItem; i++)
    {
        item = &m_currentMenuArray[i];

        switch (item->getType())
        {
            case c_menuItemNone:
                m_display.printMenuItem(item->getText());
                break;

            case c_menuItemSubMenu:
                m_display.printMenuItem(item->getText());
                m_display.printSubMenuIcon();
                break;

            default:
                break;
        }

        if (item->getType() == c_menuItemFooter)
        {
            break;
        }
    }

    if (menuTop())
    {
        m_display.printscrollDownArrow();
    }
    else if (menuBottom())
    {
        m_display.printScrollUpArrow();
    }
    else if (!menuTop() && !menuBottom())
    {
        m_display.printScrollUpArrow();
        m_display.printscrollDownArrow();
    }
}

void Menu::drawCursor()
{
    uint8_t line = constrain(m_menuCursorPosition - m_menuTopItem + 1, 1, 7); // + 1 to account for the header which is always visisble
    m_display.printMenuCursor(line);
}

bool Menu::menuTop()
{
    if (m_currentMenuArray[m_menuCursorPosition - 1].getType() == c_menuItemHeader)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Menu::menuBottom()
{
    if (m_currentMenuArray[m_menuCursorPosition + 1].getType() == c_menuItemFooter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Menu::menuCursorUp()
{
    if (!menuTop())
    {
        m_menuCursorPosition--;

        if (m_menuCursorPosition < m_menuTopItem)
        {
            m_menuTopItem--;
            m_menuBottomItem--;
        }

        displayMenu();
    }
}

void Menu::menuCursorDown()
{
    if (!menuBottom())
    {
        m_menuCursorPosition++;

        if (m_menuCursorPosition > m_menuBottomItem)
        {
            m_menuTopItem++;
            m_menuBottomItem++;
        }

        displayMenu();
    }
}

void Menu::menuSetup(MenuItem* menu)
{
    m_display.displaySetup();
    m_currentMenuArray = menu;
}

void Menu::displayMenu()
{
    m_display.clear();
    drawMenu();
    drawCursor();
    m_display.display();
}
