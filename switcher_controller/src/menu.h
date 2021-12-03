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
const uint8_t c_menuItemTypeListIntToggleHeader = 6;
const uint8_t c_menuItemTypeListIntToggle = 7;
const uint8_t c_menuItemTwoIntFullScreenHeader = 8;
const uint8_t c_menuItemTwoIntFullScreen = 9;

class MenuItem
{
    private:
        const char* m_menuItemText = NULL;
        uint8_t m_menuItemType = c_menuItemTypeNone;
        MenuItem* m_menuItemSubMenu = NULL;
        uint8_t* m_menuItemListIntToggleList = NULL;
        uint8_t* m_menuItemListIntToggleState = NULL;
        uint8_t m_menuItemListIntToggleCount = 0;

        uint8_t m_menuItemSavedTop = 0;
        uint8_t m_menuItemSavedBottom = 0;
        uint8_t m_menuItemSavedCursorPosition = 0;

    public:
        MenuItem() {}

        MenuItem(const char* text) :
            m_menuItemText(text) {}

        MenuItem(const char* text, uint8_t type) :
            m_menuItemText(text),
            m_menuItemType(type) {}

        MenuItem(const char* text, uint8_t type, MenuItem* submenu) :
            m_menuItemText(text),
            m_menuItemType(type),
            m_menuItemSubMenu(submenu) {}

        MenuItem(uint8_t* list, uint8_t* state, uint8_t count, uint8_t type) :
            m_menuItemType(type) ,
            m_menuItemListIntToggleList(list),
            m_menuItemListIntToggleState(state),
            m_menuItemListIntToggleCount(count) {}

        const char* getMenuItemText();

        uint8_t getMenuItemType();

        MenuItem* getMenuItemSubMenu();

        uint8_t* getMenuItemListIntToggleList();
        uint8_t* getMenuItemListIntToggleState();
        uint8_t getMenuItemListIntToggleCount();
        void toggleMenuItemListInt(uint8_t item);

        uint8_t getMenuItemSavedTop();
        uint8_t getMenuItemSavedBottom();
        uint8_t getMenuItemSavedCursorPosition();

        void setMenuItemSavedTop(uint8_t top);
        void setMenuItemSavedBottom(uint8_t bottom);
        void setMenuItemSavedCursorPosition(uint8_t cursor);
};

class MenuItemHeader : public MenuItem
{
    public:
        MenuItemHeader(const char* text) : MenuItem(text, c_menuItemTypeMainMenuHeader) {} // Main menu header
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

class MenuItemSubMenuHeader : public MenuItem
{
    public:
        MenuItemSubMenuHeader(const char* text) : MenuItem(text, c_menuItemTypeSubMenuHeader) {}
};

class MenuItemSubMenuBack : public MenuItem
{
    public:
        MenuItemSubMenuBack(const char* text, MenuItem* submenu) : MenuItem(text, c_menuItemTypeSubMenuBack, submenu) {}
};

class MenuItemListIntToggleHeader : public MenuItem
{
    public:
        MenuItemListIntToggleHeader(const char* text) : MenuItem(text, c_menuItemTypeListIntToggleHeader) {} // Main menu header
};

class MenuItemListIntToggle : public MenuItem
{
    public:
        MenuItemListIntToggle(uint8_t* items, uint8_t* states, uint8_t count) : MenuItem(items, states, count, c_menuItemTypeListIntToggle) {}
};

class Menu
{
    private:
        Display m_display;
        MenuItem* m_currentMenuArray = NULL;
        uint8_t m_menuMaxLines;
        uint8_t m_menuTopItem = 1;
        uint8_t m_menuBottomItem;
        uint8_t m_menuCursorPosition = 1; // 0 is always the header
        bool m_menuCursorVisible = true;
        uint8_t m_menuListCursorPosition = 1;
        bool m_menuListCursorVisible = false;

        void drawMenu();
        void drawCursor();
        void displayMenu();
        bool menuTop();
        bool menuBottom();
        void saveMenuPosition();
        void restoreMenuPosition();
        void resetMenuPosition();
        MenuItem* getCurrentMenuItem();
        MenuItem* getCurrentMenuHeader();
        uint8_t getCurrentMenuItemType();
        uint8_t getCurrentMenuHeaderType();

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