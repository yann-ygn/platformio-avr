#include <Arduino.h>

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

/**
 * @brief Drives a 8-bit current sink driver / STP08CP05
 */
class LedDriver8
{
    private:
        uint8_t m_csPin; // CS pin #

        /**
         * @brief Setup the SPI bus and select the chip
         */
        void select();

        /**
         * @brief Deselect the chip and close the SPU bus
         */
        void deselect();

    public:
        /**
         * @brief Construct a new Led Driver 8 object
         * 
         * @param cspin CS pin #
         */
        LedDriver8(uint8_t cspin) : m_csPin(cspin) { };

        /**
         * @brief Setup the µC's pins and starrt de SPI bus
         */
        void ledDriverSetup();

        /**
         * @brief Light the selected LED
         * 
         * @param led LED #
         */
        void lightLed(uint8_t led);     

        /**
         * @brief Toggles all the LED off 
         */
        void lightAllLedOff(); 
};

#endif