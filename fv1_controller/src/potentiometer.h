#include <Arduino.h>

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

/**
 * @brief test
 * 
 */
class Pot
{
    private:
        /**
         * @brief blah
         * 
         */
        byte m_pin;
        int m_currPotValue;
        int m_lastPotValue;

    public:
    /**
     * @brief Construct a new Pot object
     * 
     * @param pin 
     */
     
        Pot(byte pin) : m_pin(pin)
        {

        }
        /**
         * @brief test
         * 
         */
        void potSetup();
        int getPotValue();
        bool potTurned();
};

#endif