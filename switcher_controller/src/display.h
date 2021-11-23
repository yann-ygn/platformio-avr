#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @brief 
 *
 */
class Display
{
    private:
        Adafruit_SSD1306 m_ssd1306; // SSD1306 Display object
        uint8_t m_witdh;
        uint8_t m_height;

        uint16_t m_cursorX = 0; // X axis cursor
        uint16_t m_cursorY = 0; // Y axis cursor
        const uint8_t c_newLine = 9; // How many pixels is a new line
        const uint8_t c_maxLines = 7; // Max number of lines

        const uint8_t c_menuCursor = 26; // Menu cursor
        const uint8_t c_scrollDownArrow = 25;
        const uint8_t c_scrollUpArrow = 24;
        const uint8_t c_subMenuIcon = 16;
        const uint8_t c_subMenuBackIcon = 17;

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
         * @param wire TwoWire instance
         * @param witdh Width of the screen
         * @param height Height of the screen
         */
        Display(uint8_t witdh, uint8_t height) : m_ssd1306(witdh, height, &Wire, -1), m_witdh(witdh), m_height(height) {}

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
         * @brief 
         */
        void printScrollUpArrow();

        /**
         * @brief 
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