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
        Adafruit_SSD1306 m_ssd1306;

    public:
        /**
         * @brief Construct a new Display object
         *
         * @param wire 
         * @param witdh 
         * @param height 
         */
        Display(TwoWire* wire, uint8_t witdh, uint8_t height) : m_ssd1306(witdh, height, wire, -1) { }
};

#endif