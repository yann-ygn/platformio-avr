#include <Arduino.h>

#ifndef SELECTOR_H
#define SELECTOR_H

/**
 * @brief A rotary encoder with a switch is connected to the µC, it is monitored for changes and switch press
 */
class Selector
{
    private:
        const uint8_t m_encoderPinA = 18;
        const uint8_t m_encoderPinB = 19;
        const uint8_t m_encoderSwitch = 32;
        uint8_t m_switchState = 0;
        uint8_t m_lastSwitchState = 0;
        int m_selectorState = 0;
        int m_lastSelectorState = 0;
        const unsigned int c_encoderStates[7][4] = 
        {
            {0x0, 0x2, 0x4, 0x0},
            {0x3, 0x0, 0x1, 0x0 | 0x10},
            {0x3, 0x2, 0x0, 0x0},
            {0x3, 0x2, 0x1, 0x0},
            {0x6, 0x0, 0x4, 0x0},
            {0x6, 0x5, 0x0, 0x0 | 0x20},
            {0x6, 0x5, 0x4, 0x0},
        };

    public:
        /**
         * @brief Setup the µC's pins
         */
        void selectorSetup();

        /**
         * @brief Monitor the encoder for turns and set the counter accordingly
         */
        void selectorMove();

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool selectorSwitch();

        int m_counter = 0;
        bool m_newPreset = false;
};

#endif
