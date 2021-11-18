#include "display.h"

void Display::resetCursor()
{
    setCursorX(0);
    setCursorY(0);
}

void Display::newLine()
{
    setCursorX(0);
    setCursorY(getCursorY() + m_newLine);
}

uint16_t Display::calcTextWidth(const char * buff)
{
    int16_t x1, y1 = 0;
    uint16_t h, textWidth = 0;

    m_ssd1306.getTextBounds(buff, getCursorX(), getCursorY(), &x1, &y1, &textWidth, &h);

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

void Display::printMenuHeader(const char * buff)
{
    m_ssd1306.fillRect(0, 0, m_witdh, m_newLine, WHITE); // White background
    m_ssd1306.setTextColor(BLACK); // Invert the text color
    m_ssd1306.setTextSize(1);
    setCursorX((m_witdh / 2) - (calcTextWidth(buff) / 2)); // Set the cursor accounting for the screen and text width to center the text
    setCursorY(1); // The rect is 9p and font is 7p, offset by 1p for clarity
    m_ssd1306.print(buff);
    setCursorY(2); // The rect is 9p and font is 7p, offset by 1p for clarity
    m_ssd1306.setTextColor(WHITE); // Reset the text color
}

void Display::printMenuItem(const char * buff)
{
    newLine();
    m_ssd1306.write(rightArrow);
    setCursorX(8); // Indent to allow for the arrow
    m_ssd1306.print(buff);
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