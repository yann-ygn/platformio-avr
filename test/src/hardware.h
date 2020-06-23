#include <Arduino.h>

#ifndef HARDWARE_H
#define HARDWARE_H

/**
 * @brief Interface between the program and the hardware
 */
class Hardware
{
    private:
        uint8_t m_currentProgram = 0;
        uint8_t m_presetMode = 0;

    public:
        /**
         * @brief Setup the hardware peripherals
         */
        void hardwareSetup();

        /**
         * @brief Restore the stored hardware state
         */
        void hardwareInitialization();

        /**
         * @brief Get the Current Program object
         * 
         * @return uint8_t 
         */
        uint8_t getCurrentProgram();

        /**
         * @brief Get the Preset Mode object
         * 
         * @return uint8_t 
         */
        uint8_t getPresetMode();
};

#endif