#include <Arduino.h>

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

/**
 * @brief Drive an analog potentiometer connected to an ADC pin on the µC and read its value
 */
class AnalogPot
{
    private:
        uint8_t m_pin; // ADC pin #
        uint16_t m_currPotValue = 0;
        uint16_t m_lastPotValue = 0;

    public:
        /**
         * @brief Construct a new Pot object
         *
         * @param pin ADC pin #
         */
        AnalogPot(uint8_t pin) : m_pin(pin) { }

        /**
         * @brief Setup the µC's pin and store the current value
         */
        void analogPotSetup();

        /**
         * @brief Get the Current Pot Value object
         *
         * @return int
         */
        uint16_t getCurrentPotValue();

        /**
         * @brief Set the Current Pot Value object
         */
        void setCurrentPotValue(uint16_t value);

        /**
         * @brief Get the Last Pot Value object
         *
         * @return int
         */
        uint16_t getLastPotValue();

        /**
         * @brief Get the current value mapped to 8bits
         *
         * @return uint8_t
         */
        uint8_t getMappedCurrentPotValue();

        /**
         * @brief Check if the pot value has changed since the last cycle
         *
         * @return true
         * @return false
         */
        bool analogPotTurned();
};

class DigitalPot
{
    private:
        uint8_t m_latchPin;

    public:
        DigitalPot(uint8_t pin) : m_latchPin(pin)
        {

        }

        void digitalPotSetup();

        void setPotValue(uint8_t value);
};

#endif