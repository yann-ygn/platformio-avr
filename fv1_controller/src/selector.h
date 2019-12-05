#include <Arduino.h>

#ifndef SELECTOR_H
#define SELECTOR_H

/**
 * @brief A rotary encoder with a switch is connected to the µC, it is monitored for changes and switch press
 */
class Selector
{
    private:
        // Pins delcarations
        const uint8_t c_encoderPinA = 10; // Encoder CLK pin #, interrupt pin, to be set
        const uint8_t c_encoderPinB = 11; // Encoder DT pin #, interrupt pin, to be set
        const uint8_t c_switchPin = 32; // Encoder switch pin #, to be set
        const uint8_t c_clockPin = 7; // Shift register clock pin, to be set
        const uint8_t c_dataPin = 5; // Shift register data pin, to be set
        const uint8_t c_latchPin = 3; // Shift register latch pin, to be set

        // Switch
        uint8_t m_switchState = 0;
        uint8_t m_lastSwitchState = 0;
        unsigned long m_lastSwitchTime = 0;
        const unsigned int c_debounceTime = 300;

        // Encoder
        uint8_t m_selectorState = 0;
        uint8_t m_lastSelectorState = 0;
        const uint8_t c_encoderStates[7][4] = 
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
         * @brief Monitors the encoder switch for short press
         * 
         * @return true 
         * @return false 
         */
        bool presetSwitch();

        /**
         * @brief Set the presetMode
         */
        void setPresetMode();

        /**
         * @brief Manage the LEDs reflecting the current program or preset
         */
        void lightSelectorLed();

        int m_counter = 0;
        bool m_newProgram = false;
        bool m_presetMode = false;
        unsigned long m_now = 0;
};

#endif
