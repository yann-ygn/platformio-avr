#include <Arduino.h>

#ifndef LEDDRIVER_H
#define LEDDRIVER_H

/**
 * @brief Base class for the LED current sink drivers
 */
class LedDriver
{
    private:
        uint8_t m_csPin; // CS pin #

    protected:
        uint32_t m_blinkTime = 0;
        uint32_t m_lastBlinkTime = 0;
        uint8_t m_lastBlinkState = 0;
        uint16_t m_ledDriverMask = 0;

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
         * @brief Construct a new Led Driver object
         *
         * @param cspin CS pin #
         */
        LedDriver(uint8_t cspin) : m_csPin(cspin) { }

        /**
         * @brief Setup the µC's pins and start the SPI bus
         */
        void ledDriverSetup();
};

/**
 * @brief Drives a 8bit current sink driver to manage 4 bicolor LEDs
 */
class LedDriver8 : public LedDriver
{
    public:
        /**
         * @brief Construct a new Led Driver 8 object
         *
         * @param cspin CS pin #
         */
        LedDriver8(uint8_t cspin) : LedDriver(cspin) { }

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

        #ifdef DEBUG
            /**
             * @brief Dummy test method
             */
            void testAllLed();
        #endif
};

/**
 * @brief Drives a 16bit current sink driver to manage 8 bicolor LEDs
 */
class LedDriver16 : public LedDriver
{
    public:
        /**
         * @brief Construct a new Led Driver 16 object
         *
         * @param cspin CS pin #
         */
        LedDriver16(uint8_t cspin) : LedDriver(cspin) { };

        /**
         * @brief Light the selected LED
         *
         * @param led LED #
         */
        void lightLed(uint8_t led);

        /**
         * @brief Lights the 2 selected LEDs
         *
         * @param led LED #
         */
        void lightLed2(uint8_t led);

        /**
         * @brief Toggles all the LED off
         */
        void lightAllLedOff();

        /**
         * @brief Blink an LED with a given inrterval
         *
         * @param led LED #
         * @param interval Interval in ms
         */
        void blinkLed(uint8_t led, uint8_t interval);

        /**
         * @brief Blink two LEDs with a given inrterval
         *
         * @param led LED #
         * @param interval Interval in ms
         */
        void blinkLed2(uint8_t led, uint8_t interval);

        /**
         * @brief Reset the blink state
         *
         */
        void resetBlink();

        void setLedStateByMask(uint16_t mask);
        uint16_t getLedDriverMask();

        #ifdef DEBUG
            /**
             * @brief Dummy test method
             */
            void testAllLed();
        #endif
};

#endif