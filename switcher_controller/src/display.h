#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//#include "fonts/SourceCodePro_Regular5pt7b.h"
//#include "fonts/SourceCodePro_Regular6pt7b.h"
#include "fonts/SourceCodePro_Bold32pt7b.h"

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief A display manages a physical OLED screen, it is defined by a width, a height and a maximum number of lines of a determine size
 *
 */
class Display
{
    private:
        Adafruit_SSD1306 m_ssd1306; // SSD1306 Display object
        uint8_t m_witdh; // Width of the display in pixel
        uint8_t m_height; // Height of the display in pixel

        uint16_t m_cursorX = 0; // X axis cursor
        uint16_t m_cursorY = 0; // Y axis cursor
        const uint8_t c_newLine; // How many pixels is a new line
        const uint8_t c_maxLines; // Max number of lines
        const uint8_t c_headerOffset; // The header is typically c_newLine + 2 to allow for the text to be centerex vertically
        const uint8_t c_newTab = 8; // Arbitrary "tab" value in pixel used to ident the text

        const uint8_t c_menuCursor = 26; // Menu cursor symbol
        const uint8_t c_scrollDownArrow = 25; // Scroll down symbol
        const uint8_t c_scrollUpArrow = 24; // Scroll up symbol
        const uint8_t c_subMenuIcon = 16; // Submenu symbol
        const uint8_t c_subMenuBackIcon = 17; // Submenu back symbol

        /**
         * @brief Reset X/Y cursors
         */
        void resetCursor();

        /**
         * @brief Adjust the X/Y cursor to account for a new line
         */
        void newLine();

        /**
         * @brief Calculate the width of a string
         *
         * @param text Text input
         * @return uint16_t Witdh of the string
         */
        uint16_t calcTextWidth(const char* text);

    public:
        /**
         * @brief Construct a new Display object
         *
         * @param witdh Width of the screen
         * @param height Height of the screen
         */
        Display(uint8_t witdh, uint8_t height, uint8_t newline, uint8_t maxlines, uint8_t headeroffset) :
            m_ssd1306(witdh, height, &Wire, -1),
            m_witdh(witdh),
            m_height(height),
            c_newLine(newline),
            c_maxLines(maxlines),
            c_headerOffset(headeroffset) {}

        /**
         * @brief Initialize the base display
         */
        void displaySetup();

        /**
         * @brief Clear the display
         */
        void clear();

        /**
         * @brief Display
         */
        void display();

        /**
         * @brief Print the menu header, inverse text and background
         *
         * @param text Text to print
         */
        void printMenuHeader(const char* text);

        /**
         * @brief Print a menu item, slight indent
         *
         * @param text Text to print
         */
        void printMenuItem(const char* text);

        /**
         * @brief Print a centered and ordered list of numbers, highlighted or not
         *
         * @param item Text to print
         * @param highlight 1 = hightlighted, 0 = not highlighted
         * @param count Number of items in the array
         */
        void printListNumbers(uint8_t* items, uint8_t* states, /**uint8_t* orders,**/ uint8_t count);

        /**
         * @brief Print a sub icon at the end of the current line
         */
        void printSubMenuIcon();

        /**
         * @brief Print a sub icon at the end of the current line
         */
        void printSubMenuBackIcon();

        /**
         * @brief Draw the menu cursor at y = line * newline
         */
        void printMenuCursor(uint8_t line);

        /**
         * @brief Draw the list cursor at x = column * text lenght
         */
        void printListMenuCursor(uint8_t column);

        /**
         * @brief Print a new line
         */
        void printNewLine();

        /**
         * @brief Prints two number with a separator in full screen
         *
         * @param number
         * @param number2
         */
        void printTwoIntFullScreen(uint8_t* number, uint8_t* number2);

        /**
         * @brief Print the scroll arrow pointing up
         */
        void printScrollUpArrow();

        /**
         * @brief Print the scroll arrow pointing down
         */
        void printscrollDownArrow();

        /**
         * @brief Get the Cursor X object
         */
        uint16_t getCursorX();

        /**
         * @brief Set the Cursor X object
         *
         * @param x Cursor value
         */
        void setCursorX(uint16_t x);

        /**
         * @brief Get the Cursor Y object
         */
        uint16_t getCursorY();

        /**
         * @brief Set the Cursor Y object
         *
         * @param y Cursor value
         */
        void setCursorY(uint16_t y);

        /**
         * @brief Get the Width object
         */
        uint8_t getWidth();

        /**
         * @brief Get the Height object
         */
        uint8_t getHeight();
};

#endif