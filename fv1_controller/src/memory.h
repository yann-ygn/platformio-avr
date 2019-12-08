#include <Arduino.h>

#include "M95256.h"

#ifndef MEMORY_H
#define MEMORY_H

/**
 * @brief Manages 
 */
class Memory
{
    private:
        M95256 eeprom0;
    

    public:
        Memory() : eeprom0(53)
        {
            
        }
        byte readBypassSwState();
        void writeBypassSwState(byte state);
};

#endif