#include "display.h"

void Display::resetCursor()
{
    setCursorX(0);
    setCursorY(0);
}

void Display::newLine()
{
    setCursorX(0);
    setCursorY(getCursorY() + c_newLine);
}

uint16_t Display::calcTextWidth(const char* text)
{
    int16_t x1, y1 = 0;
    uint16_t h, textWidth = 0;

    m_ssd1306.getTextBounds(text, getCursorX(), getCursorY(), &x1, &y1, &textWidth, &h);

    return textWidth;
}

void Display::clear()
{
    m_ssd1306.clearDisplay();
}

void Display::display()
{
    m_ssd1306.display();
}

void Display::displaySetup()
{
    m_ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void Display::printMenuHeader(const char* text)
{
    resetCursor();
    m_ssd1306.fillRect(0, 0, m_witdh, c_newLine, WHITE); // White background
    m_ssd1306.setTextColor(BLACK); // Invert the text color
    m_ssd1306.setTextSize(1);
    setCursorX((m_witdh / 2) - (calcTextWidth(text) / 2)); // Set the cursor accounting for the screen and text width to center the text
    setCursorY(1); // The rect is 9p and font is 7p, offset by 1p for clarity
    m_ssd1306.print(text);
    setCursorY(2); // The rect is 9p and font is 7p, offset by 1p for clarity
    m_ssd1306.setTextColor(WHITE); // Reset the text color
}

void Display::printMenuItem(const char* text)
{
    newLine();
    setCursorX(8); // Indent to account for the arrow cursor
    m_ssd1306.print(text);
}

void Display::printSubMenuIcon()
{
    setCursorX(getWidth() - 16);
    m_ssd1306.write(c_subMenuIcon);
}

void Display::printMenuCursor(uint8_t line)
{
    setCursorX(0);
    setCursorY((line * c_newLine) + 2);
    m_ssd1306.write(c_menuCursor);
}

void Display::printScrollUpArrow()
{
    setCursorX(getWidth() - 8);
    setCursorY(0 + c_newLine + 2);
    m_ssd1306.write(c_scrollUpArrow);
}

void Display::printscrollDownArrow()
{
    setCursorX(getWidth() - 8);
    setCursorY(getHeight() - c_newLine);
    m_ssd1306.write(c_scrollDownArrow);
}

uint16_t Display::getCursorX()
{
    return m_cursorX;
}

void Display::setCursorX(uint16_t x)
{
    m_cursorX = x;
    m_ssd1306.setCursor(x, getCursorY());
}

uint16_t Display::getCursorY()
{
    return m_cursorY;
}

void Display::setCursorY(uint16_t y)
{
    m_cursorY = y;
    m_ssd1306.setCursor(getCursorX(), y);
}

uint8_t Display::getWidth()
{
    return m_witdh;
}

uint8_t Display::getHeight()
{
    return m_height;
}