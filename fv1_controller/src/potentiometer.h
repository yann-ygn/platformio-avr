#include <Arduino.h>

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

/**
 * @brief An analog potentiometer connected to an ADC pin on the µC. The object is instantiated with the pin number used.
 * The potentiometer needs to be setup, can check if its value changed since the last cycle and return its current value. 
 */
class Pot
{
    private:
        uint8_t m_pin;
        uint16_t m_currPotValue = 0;
        uint16_t m_lastPotValue = 0;

    public:
        /**
         * @brief Construct a new Pot object
         * 
         * @param pin The potentiometer pin #
         */     
        Pot(uint8_t pin) : m_pin(pin)
        {

        }

        /**
         * @brief Setup the µC's pin and store the current value
         */
        void potSetup();

        /**
         * @brief Get the Current Pot Value object
         * 
         * @return int 
         */
        uint16_t getCurrentPotValue();
        
        /**
         * @brief Get the Last Pot Value object
         * 
         * @return int 
         */
        uint16_t getLastPotValue();

        /**
         * @brief Get the Mapped Pot Value object
         * 
         * @return uint8_t 
         */
        uint8_t getMappedPotValue();

        /**
         * @brief Check if the pot value has changed since the last cycle
         * 
         * @return true 
         * @return false 
         */
        bool potTurned();
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

        void setPotValue(uint16_t value);
};

#endif