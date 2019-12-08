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
        byte m_pin;
        int m_currPotValue = 0;
        int m_lastPotValue = 0;

    public:
        /**
         * @brief Construct a new Pot object
         * 
         * @param pin The potentiometer pin #
         */     
        Pot(byte pin) : m_pin(pin)
        {

        }

        /**
         * @brief Setup the µC's pin and store the current value
         */
        void potSetup();

        /**
         * @brief Get the stored pot current value
         * 
         * @return int 
         */
        int getPotValue();

        /**
         * @brief Check if the pot value has changed since the last cycle
         * 
         * @return true 
         * @return false 
         */
        bool potTurned();
};

#endif