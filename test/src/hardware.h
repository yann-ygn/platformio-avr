#include <Arduino.h>

#ifndef HARDWARE_H
#define HARDWARE_H

/**
 * @brief Interface between the program and the hardware
 */
class Hardware
{
    private:
        uint8_t m_bypassState = 0;
        uint8_t m_currentProgram = 0;
        uint8_t m_presetMode = 0;

        bool m_bypassSwitchPress = false;
        bool m_selectorMove = false;
        bool m_selectorSwitchPress = false;
        bool m_selectorSwitchLongPress = false;

    public:
        /**
         * @brief Setup the hardware devices
         */
        void hardwareSetup();

        /**
         * @brief Restore the stored hardware state
         */
        void hardwareInitialization();

        /**
         * @brief Poll the various devices
         */
        void hardwarePoll();

        /**
         * @brief Switch the pedal on/off
         */
        void bypassSwitch();

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

        /**
         * @brief Get the Bypass Switch Press object
         * 
         * @return true 
         * @return false 
         */
        bool getBypassSwitchPress();

        /**
         * @brief Get the Selector Move object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorMove();

        /**
         * @brief Get the Selector Switch Press object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorSwitchPress();

        /**
         * @brief Get the Selector Switch Long Press object
         * 
         * @return true 
         * @return false 
         */
        bool getSelectorSwitchLongPress();
};

#endif