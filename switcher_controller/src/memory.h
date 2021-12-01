#include <Arduino.h>

#include "eeprom.h"

#ifndef MEMORY_H
#define MEMORY_H

/**
 * @brief Manages
 */
class Memory
{
    private:
        Eeprom eeprom0;

        const uint16_t c_initialSetupStateAddress = 0;

    public:
        Memory(uint8_t pin) : eeprom0(pin) {}

        void memorySetup();
        void memoryInitialization();
        void memoryReset();
        void memoryTest();

        uint8_t readInitialSetupState();
        void writeInitialSetupState(uint8_t state);
};

#endif