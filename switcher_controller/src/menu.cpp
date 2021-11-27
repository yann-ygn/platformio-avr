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

Loop* MenuItem::getMenuItemLoops()
{
    return m_menuItemLoops;
}

uint8_t MenuItem::getMenuItemSavedTop()
{
    return m_menuItemSavedTop;
}

uint8_t MenuItem::getMenuItemSavedBottom()
{
    return m_menuItemSavedBottom;
}

uint8_t MenuItem::getMenuItemSavedCursorPosition()
{
    return m_menuItemSavedCursorPosition;
}

void MenuItem::setMenuItemSavedTop(uint8_t top)
{
    m_menuItemSavedTop = top;
}

void MenuItem::setMenuItemSavedBottom(uint8_t bottom)
{
    m_menuItemSavedBottom = bottom;
}

void MenuItem::setMenuItemSavedCursorPosition(uint8_t cursor)
{
    m_menuItemSavedCursorPosition = cursor;
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

            case c_menuItemTypeLoopSubMenu:
            {
                uint8_t items[6];
                uint8_t states[6];

                Loop* loops = item->getMenuItemLoops();

                for (uint8_t i = 0; i < 6; i++)
                {
                    items[i] = loops[i].getId();
                    states[i] = loops[i].getState();
                }

                m_display.printListNumbers(items, states, 6);

                break;
            }

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

bool Menu::menuTop()
{
    if (m_currentMenuArray[m_menuCursorPosition - 1].getMenuItemType() == c_menuItemTypeMainMenuHeader ||
        m_currentMenuArray[m_menuCursorPosition - 1].getMenuItemType() == c_menuItemTypeSubMenuHeader)
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

void Menu::saveMenuPosition()
{
    m_currentMenuArray[0].setMenuItemSavedTop(m_menuTopItem);
    m_currentMenuArray[0].setMenuItemSavedBottom(m_menuBottomItem);
    m_currentMenuArray[0].setMenuItemSavedCursorPosition(m_menuCursorPosition);
}

void Menu::restoreMenuPosition()
{
    m_menuTopItem = m_currentMenuArray[0].getMenuItemSavedTop();
    m_menuBottomItem = m_currentMenuArray[0].getMenuItemSavedBottom();
    m_menuCursorPosition = m_currentMenuArray[0].getMenuItemSavedCursorPosition();
}

void Menu::resetMenuPosition()
{
    m_menuTopItem = 1;
    m_menuBottomItem = m_menuMaxLines;
    m_menuCursorPosition = 1;
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
    MenuItem* item = &m_currentMenuArray[m_menuCursorPosition];

    switch (item->getMenuItemType())
    {
        case c_menuItemTypeSubMenu:
            if (item->getMenuItemSubMenu() != NULL)
            {
                saveMenuPosition();
                m_currentMenuArray = item->getMenuItemSubMenu();
                resetMenuPosition();

                displayMenu();
                break;
            }

        case c_menuItemTypeSubMenuBack:
            MenuItem* menuHeader = &m_currentMenuArray[0];

            if (menuHeader->getMenuItemType() == c_menuItemTypeSubMenuHeader)
            {
                m_currentMenuArray = menuHeader->getMenuItemSubMenu();

                restoreMenuPosition();

                displayMenu();
                break;
            }
    }
}

