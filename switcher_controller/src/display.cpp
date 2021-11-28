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
    setCursorY(c_headerOffset / 2); // The rect is 9p and font is 7p, offset by 1p for clarity
    m_ssd1306.print(text);
    setCursorY(c_headerOffset); // The rect is 9p and font is 7p, offset by 1p for clarity
    m_ssd1306.setTextColor(WHITE); // Reset the text color
}

void Display::printMenuItem(const char* text)
{
    newLine(); // Set the Y cursor to a new line
    setCursorX(c_newTab); // Indent to account for the arrow cursor
    m_ssd1306.print(text);
}

void Display::printListNumbers(uint8_t* items, uint8_t* states, uint8_t count)
{
    uint8_t cursor = getCursorY();
    setCursorY(m_height / 2);
    setCursorX(0);

    for (uint8_t i = 1; i <= count; i++)
    {
        if (states[i])
        {
            m_ssd1306.setTextColor(BLACK, WHITE);
            m_ssd1306.print(items[i]);
            m_ssd1306.setTextColor(WHITE);
            setCursorX(getCursorX() + c_newTab);
        }
        else
        {
            m_ssd1306.print(items[i]);
            setCursorX(getCursorX() + c_newTab);
        }

        if (i < count)
        {
            m_ssd1306.write(c_menuCursor);
            setCursorX(getCursorX() + c_newTab);
        }
    }

    setCursorY(cursor);
    newLine();
}

void Display::printNewLine()
{
    newLine();
}

void Display::printSubMenuIcon()
{
    setCursorX(getWidth() - (c_newTab * 2)); // End of the line minues 2 tabs, first tab would be the scroll up/down arrows
    m_ssd1306.write(c_subMenuIcon);
}

void Display::printSubMenuBackIcon()
{
    setCursorX(getWidth() - (c_newTab * 2)); // End of the line minues 2 tabs, first tab would be the scroll up/down arrows
    m_ssd1306.write(c_subMenuBackIcon);
}

void Display::printMenuCursor(uint8_t line)
{
    setCursorX(0);
    setCursorY((line * c_newLine) + c_headerOffset);
    m_ssd1306.write(c_menuCursor);
}

void Display::printListMenuCursor(uint8_t column)
{
    setCursorY((m_height / 2) - c_newTab);
    setCursorX(map(column, 1, 6, 0, 80));
    m_ssd1306.write(c_scrollDownArrow);
}

void Display::printScrollUpArrow()
{
    setCursorX(getWidth() - c_newTab); // End of the line minus one tab
    setCursorY(0 + c_newLine + c_headerOffset); // Top of the screen + new line + header off set
    m_ssd1306.write(c_scrollUpArrow);
}

void Display::printscrollDownArrow()
{
    setCursorX(getWidth() - 8); // End of the line minus one tab
    setCursorY(getHeight() - c_newLine); // Bottomof the screen minus one line
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