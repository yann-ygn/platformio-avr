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

        bool m_effectIsDelay = false;
        uint16_t m_effectMinInterval = 0;
        uint16_t m_effectMaxInterval = 0;
        bool m_effectHasTapEnabled = false;
        bool m_effectHasPot0Enabled = false;
        bool m_effectHasPot1Enabled = false;
        bool m_effectHasPot2Enabled = false;

        uint8_t m_tapState = 0;
        uint8_t m_divState = 0;
        uint8_t m_divValue = 0;
        uint16_t m_interval = 0;
        uint16_t m_divInterval = 0;

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
         * @brief Initialize the memory and set the midi channel
         */
        void hardwareInitialization();

        /**
         * @brief Restore the last stored pedal state
         */
        void restoreLastState();

        /**
         * @brief Poll the various devices
         */
        void hardwarePoll();

        /**
         * @brief Switch the pedal on/off
         */
        void bypassSwitch();

        /**
         * @brief Change between preset and program mode
         */
        void presetModeSwitch();

        /**
         * @brief Load a program from memory
         */
        void loadProgram();

        /**
         * @brief Load a preset from memory
         */
        void loadPreset();

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

        /**
         * @brief Get the Bypass State object
         * 
         * @return uint8_t 
         */
        uint8_t getBypassState();  
};

#endif