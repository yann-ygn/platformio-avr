#include "menu.h"

const char* MenuItem::getMenuItemText()
{
    return m_menuItemText;
}

uint8_t MenuItem::getMenuItemType()
{
    return m_menuItemType;
}

MenuItem* MenuItem::getMenuItemSubMenu()
{
    return m_menuItemSubMenu;
}

void Menu::drawMenu()
{
    MenuItem* item = &m_currentMenuArray[0]; // 0 is always the header
    m_display.printMenuHeader(item->getMenuItemText()); // Draw the menu header

    for (uint8_t i = m_menuTopItem; i <= m_menuBottomItem; i++)
    {
        item = &m_currentMenuArray[i];

        switch (item->getMenuItemType())
        {
            case c_menuItemTypeNone:
                m_display.printMenuItem(item->getMenuItemText());
                break;

            case c_menuItemTypeSubMenu:
                m_display.printMenuItem(item->getMenuItemText());
                m_display.printSubMenuIcon();
                break;

            case c_menuItemTypeSubMenuBack:
                m_display.printMenuItem(item->getMenuItemText());
                m_display.printSubMenuBackIcon();
                break;

            default:
                break;
        }

        if (item->getMenuItemType() == c_menuItemTypeFooter)
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

void Menu::displayMenu()
{
    m_display.clear();
    drawMenu();
    drawCursor();
    m_display.display();
}

void Menu::resetMenu(bool history)
{
    if (history)
    {
        m_menuCursorPosition = m_menuPreviousCursorPosition;
        m_menuTopItem = m_menuPreviousTopItem;
        m_menuBottomItem = m_menuPreviousBottomItem;
    }
    else
    {
        m_menuPreviousCursorPosition = m_menuCursorPosition;
        m_menuPreviousTopItem = m_menuTopItem;
        m_menuPreviousBottomItem = m_menuBottomItem;

        m_menuCursorPosition = 1;
        m_menuTopItem = 1;
        m_menuBottomItem = m_menuMaxLines - 1;
    }

    displayMenu();
}

bool Menu::menuTop()
{
    if (m_currentMenuArray[m_menuCursorPosition - 1].getMenuItemType() == c_menuItemTypeMainMenuHeader)
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
    if (m_currentMenuArray[m_menuCursorPosition + 1].getMenuItemType() == c_menuItemTypeFooter)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Menu::menuSetup(MenuItem* menu)
{
    m_display.displaySetup();
    m_currentMenuArray = menu;
    displayMenu();
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

void Menu::menuCursorEnter()
{
    Serial.println("Prout");

    MenuItem* item = &m_currentMenuArray[m_menuCursorPosition];

    switch (item->getMenuItemType())
    {
        case c_menuItemTypeSubMenu:
            Serial.println("Prout2");
            if (item->getMenuItemSubMenu() != NULL)
            {
                m_currentMenuArray = item->getMenuItemSubMenu();

                resetMenu(false);
                break;
            }

        case c_menuItemTypeSubMenuBack:
            Serial.println("Prout3");
            MenuItem* menuHeader = &m_currentMenuArray[0];

            if (menuHeader->getMenuItemType() == c_menuItemTypeSubMenuHeader)
            {
                m_currentMenuArray = menuHeader->getMenuItemSubMenu();

                resetMenu(true);
                break;
            }
    }
}