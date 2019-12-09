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

        const byte c_bypassStateAddress = 0;
        const byte c_tapStateAddress = 1;
        const byte c_presetModeAddress = 2;
    

    public:
        Memory() : eeprom0(53)
        {
            
        }

        void memorySetup();

        byte readBypassState();
        void writeBypassState(byte state);
};

#endif