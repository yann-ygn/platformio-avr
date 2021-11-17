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

void Display::displaySetup()
{
    m_ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void Display::clear()
{
    m_ssd1306.clearDisplay();
}

void Display::display()
{
    m_ssd1306.display();
}

void Display::printMenuHeader(const char * buff)
{
    clear();
    m_ssd1306.fillRect(0, 0, m_witdh, m_newLine, WHITE);
    m_ssd1306.setTextColor(BLACK);
    m_ssd1306.setTextSize(1);
    setCursorY(1);
    m_ssd1306.print(buff);
    display();
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