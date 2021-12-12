#include "menu.h"

const char* MenuItem::getMenuItemText()
{
    return m_menuItemText;
}

void MenuItem::setMenuItemText(const char* text)
{
    m_menuItemText = text;
}

uint8_t* MenuItem::getMenuItemIntValue()
{
    return m_menuItemIntValue;
}

void MenuItem::setMenuItemIntValue(uint8_t* value)
{
    m_menuItemIntValue = value;
}

uint8_t MenuItem::getMenuItemType()
{
    return m_menuItemType;
}

MenuItem* MenuItem::getMenuItemSubMenu()
{
    return m_menuItemSubMenu;
}

uint8_t* MenuItem::getMenuItemListIntToggleList()
{
    return m_menuItemListIntToggleList;
}

uint8_t* MenuItem::getMenuItemListIntToggleState()
{
    return m_menuItemListIntToggleState;
}

uint8_t MenuItem::getMenuItemListIntToggleCount()
{
    return m_menuItemListIntToggleCount;
}

void MenuItem::setMenuItemListIntToggleList(uint8_t* list)
{
    m_menuItemListIntToggleList = list;
}

void MenuItem::setMenuItemListIntToggleState(uint8_t* state)
{
    m_menuItemListIntToggleState = state;
}

void MenuItem::setMenuItemListIntToggleCount(uint8_t count)
{
    m_menuItemListIntToggleCount = count;
}

void MenuItem::toggleMenuItemListInt(uint8_t item)
{
    uint8_t* states = getMenuItemListIntToggleState();
    uint8_t state = states[item];
    states[item] = !state;
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
    MenuItem* item = getCurrentMenuHeader();
    m_display.printMenuHeader(item->getMenuItemText());

    if (getCurrentMenuHeaderType() == c_menuItemTypeListIntToggleHeader)
    {
        for (uint8_t i = m_menuTopItem; i <= m_menuBottomItem; i++)
        {
            item = &m_currentMenuArray[i];

            switch (item->getMenuItemType())
            {
                case c_menuItemTypeNone:
                    if (item->getMenuItemText() != NULL)
                    {
                        m_display.printMenuItem(item->getMenuItemText());
                    }
                    else
                    {
                        m_display.printNewLine();
                    }
                    break;

                case c_menuItemTypeSubMenuBack:
                    m_display.printMenuItem(item->getMenuItemText());
                    m_display.printSubMenuBackIcon();
                    break;

                case c_menuItemTypeListIntToggle:
                    m_display.printListNumbers(item->getMenuItemListIntToggleList(), item->getMenuItemListIntToggleState(), item->getMenuItemListIntToggleCount());
                    break;
            }
        }
    }
    else if (getCurrentMenuHeaderType() == c_menuItemTwoIntFullScreenHeader)
    {
        uint8_t* values[2];

        for (uint8_t i = 1; i < 3; i++)
        {
            item = &m_currentMenuArray[i];
            values[i-1] = item->getMenuItemIntValue();
        }

        m_display.printTwoIntFullScreen(values[0], values[1]);
    }
    else
    {
        for (uint8_t i = m_menuTopItem; i <= m_menuBottomItem; i++)
        {
            item = &m_currentMenuArray[i];

            switch (item->getMenuItemType())
            {
                case c_menuItemTypeNone:
                    if (item->getMenuItemText() != NULL)
                    {
                        m_display.printMenuItem(item->getMenuItemText());
                    }
                    else
                    {
                        m_display.printNewLine();
                    }
                    break;

                case c_menuItemTypeSubMenu:
                    m_display.printMenuItem(item->getMenuItemText());
                    m_display.printSubMenuIcon();
                    break;

                case c_menuItemTypeSubMenuBack:
                    m_display.printMenuItem(item->getMenuItemText());
                    m_display.printSubMenuBackIcon();
                    break;

                case c_menuItemTypeListIntToggle:
                    m_display.printListNumbers(item->getMenuItemListIntToggleList(), item->getMenuItemListIntToggleState(), item->getMenuItemListIntToggleCount());
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
}

void Menu::drawCursor()
{
    if (m_menuListCursorVisible)
    {
        m_display.printListMenuCursor(m_menuListCursorPosition);
    }

    if (m_menuCursorVisible)
    {
        uint8_t line = constrain(m_menuCursorPosition - m_menuTopItem + 1, 1, 7); // + 1 to account for the header which is always visisble
        m_display.printMenuCursor(line);
    }
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
        m_currentMenuArray[m_menuCursorPosition - 1].getMenuItemType() == c_menuItemTypeSubMenuHeader ||
        m_currentMenuArray[m_menuCursorPosition - 1].getMenuItemType() == c_menuItemTypeListIntToggleHeader)
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
    m_menuListCursorPosition = 1;
}

MenuItem* Menu::getCurrentMenuItem()
{
    return &m_currentMenuArray[m_menuCursorPosition];
}

MenuItem* Menu::getCurrentMenuHeader()
{
    return &m_currentMenuArray[0];
}

uint8_t Menu::getCurrentMenuItemType()
{
    return getCurrentMenuItem()->getMenuItemType();
}

uint8_t Menu::getCurrentMenuHeaderType()
{
    return m_currentMenuArray[0].getMenuItemType();
}

void Menu::menuSetup(MenuItem* menu, bool display)
{
    m_display.displaySetup();
    m_currentMenuArray = menu;

    if (display)
    {
        displayMenu();
    }
}

void Menu::menuCursorUp()
{
    if (getCurrentMenuHeaderType() == c_menuItemTypeListIntToggleHeader)
    {
        MenuItem* item = getCurrentMenuItem();

        if (item->getMenuItemType() == c_menuItemTypeListIntToggle)
        {
            m_menuListCursorVisible = true;
            m_menuCursorVisible = false;

            if (m_menuListCursorPosition < item->getMenuItemListIntToggleCount())
            {
                m_menuListCursorPosition++;
            }
            else
            {
                m_menuCursorPosition = m_menuMaxLines - 1;
                m_menuListCursorVisible = false;
                m_menuCursorVisible = true;
            }
        }
    }
    else
    {
        m_menuListCursorVisible = false;
        m_menuCursorVisible = true;

        if (!menuTop())
        {
            m_menuCursorPosition--;

            if (m_menuCursorPosition < m_menuTopItem)
            {
                m_menuTopItem--;
                m_menuBottomItem--;
            }
        }
    }

    Serial.println(m_menuCursorPosition);
    Serial.println(m_menuListCursorPosition);
    displayMenu();
}

void Menu::menuCursorDown()
{
    if (getCurrentMenuHeaderType() == c_menuItemTypeListIntToggleHeader)
    {
        MenuItem* item = getCurrentMenuItem();

        if (item->getMenuItemType() == c_menuItemTypeListIntToggle)
        {
            m_menuListCursorVisible = true;
            m_menuCursorVisible = false;

            if (m_menuListCursorPosition > 1)
            {
                m_menuListCursorPosition--;
            }
        }
        else
        {
            m_menuCursorPosition = 1;
            m_menuListCursorVisible = true;
            m_menuCursorVisible = false;
        }
    }
    else
    {
        m_menuListCursorVisible = false;
        m_menuCursorVisible = true;

        if (!menuBottom())
        {
            m_menuCursorPosition++;

            if (m_menuCursorPosition > m_menuBottomItem)
            {
                m_menuTopItem++;
                m_menuBottomItem++;
            }
        }
    }

    Serial.println(m_menuCursorPosition);
    Serial.println(m_menuListCursorPosition);
    displayMenu();
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

                item = &m_currentMenuArray[0];

                if (item->getMenuItemType() == c_menuItemTypeListIntToggleHeader)
                {
                    m_menuCursorVisible = false;
                    m_menuListCursorVisible = true;
                }
                else
                {
                    m_menuCursorVisible = true;
                    m_menuListCursorVisible = false;
                }

                displayMenu();
                break;
            }

        case c_menuItemTypeSubMenuBack:
            if (item->getMenuItemSubMenu() != NULL)
            {
                m_currentMenuArray = item->getMenuItemSubMenu();

                restoreMenuPosition();

                displayMenu();
                break;
            }

        case c_menuItemTypeListIntToggle:
            item->toggleMenuItemListInt(m_menuListCursorPosition);
            displayMenu();

            break;
    }
}

void Menu::menuRefresh()
{
    displayMenu();
}

uint8_t Menu::getMenuType()
{
    return getCurrentMenuHeaderType();
}

uint8_t Menu::getCurrentItemType()
{
    return getCurrentMenuItemType();
}
