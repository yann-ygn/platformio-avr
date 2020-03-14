#include <Arduino.h>

#ifndef TAP_H
#define TAP_H

/**
 * @brief A switch is connected to the µC, and is monitored for press to calculate
 * the mean value between a defined maximum number of presses. An LED is 
 * flashed at that same frequency.
 * The switch is also monitored for long presses to set the delay division. Three 
 * LEDs are used to indicate the current division value between 1/2, 1/3 and 1/4.
 */
class Tap
{
    private:
        // Pins declarations
        const uint8_t c_swPin = 19; // Footswitch pin #, to be set.
        const uint8_t c_ledPin = 15; // LED pin #, to be set.
        const uint8_t c_latchPin = 21; // Shift register latch pin, to be set. 

        // Switch -> Tap
        uint8_t m_tapState = 0; // Is tap enabled
        uint8_t m_switchState = 0;
        uint8_t m_lastSwitchState = 0;
        unsigned long m_firstTapTime = 0;
        unsigned long m_lastTaptime = 0;
        uint8_t m_timesTapped = 0;
        const uint8_t c_maxTaps = 3; // The number of taps before the mean value is calculated
        uint16_t m_interval = 0;
        uint16_t m_minInterval = 0; // The absolute minimum delay value in ms, set by the current program
        uint16_t m_maxInterval = 1000; // The absolute maximum delay value in ms, set by the current program
        const uint8_t c_debounceTime = 100; // Minimum time between two footswich press

        // Tap LED
        uint8_t m_blinkValue = 0;

        // Switch -> Division
        bool m_divState = 0; // Is div enabled
        bool m_longTapPress = false;
        uint8_t m_divValue = 1;
        const uint16_t c_divDebounceTime = 1000; // Minimum time between 2 long footswitch press
        uint16_t m_divInterval = 0;

    public:
        /**
         * @brief Setup the µC's pins 
         */
        void tapSetup();

        /**
         * @brief Read the footswitch state
         * 
         * @return true if the conditions are met to trigger a tap count
         * @return false 
         */
        bool tapPressed();

        /**
         * @brief Check for tap tempo timeouts
         * 
         * @return true if the conditions are met to trigger a tap count reset
         * @return false 
         */
        bool tapTimeout();

        /**
         * @brief Resets the tap tempo counter 
         */
        void tapReset();

        /**
         * @brief Set the Tap counter
         */
        void setTapCount();

        /**
         * @brief Calculate the delay interval based on the average tap tempo time
         */
        void calculateInterval();

        /**
         * @brief Calculate the divided interval value based on the current delay interval and divider
         */
        void calculateDivInterval();

        /**
         * @brief Blink the LED according to the set interval
         * 
         * @param interval Optional if the tap interval is not used
         */
        void blinkTapLed(uint16_t interval = 0);

        /**
         * @brief Turn off the tap LED
         * 
         */
        void turnOffTapLed();

        /**
         * @brief Read the footswitch state
         * 
         * @return true if the conditions are met to trigger a division change
         * @return false 
         */
        bool divPressed();

        /**
         * @brief Set the divider value
         */
        void setDivision();

        /**
         * @brief Light the correct LED according to the current set divider 
         */
        void lightDivLed();

        /**
         * @brief Sends a value to the shift register
         * 
         * @param value 
         */
        void shiftReg(uint8_t value);

        /**
         * @brief Set the Div Interval object
         * 
         * @param interval 
         */
        void setDivInterval(uint16_t interval);

        /**
         * @brief Get the Div Interval object
         * 
         * @return uint16_t 
         */
        uint16_t getDivInterval();

        /**
         * @brief Get the Div Value object
         * 
         * @return uint8_t 
         */
        uint8_t getDivValue();

        /**
         * @brief Set the Div Value object
         * 
         * @param value 
         */
        void setDivValue(uint8_t value);

        /**
         * @brief Get the current calculated interval
         * 
         * @return uint16_t 
         */
        uint16_t getInterval();

        /**
         * @brief Set the Interval object
         * 
         * @param interval 
         */
        void setInterval(uint16_t interval);

        /**
         * @brief Get the Tap State object
         * 
         * @return uint8_t 
         */
        uint8_t getTapState();

        /**
         * @brief Set the Tap State object
         * 
         * @param state 
         */
        void setTapState(uint8_t state);

        /**
         * @brief Get the Div State object
         * 
         * @return uint8_t 
         */
        uint8_t getDivState();

        /**
         * @brief Set the Div State object
         * 
         * @param state 
         */
        void setDivState(uint8_t state);

        /**
         * @brief Get the Max Interval object
         * 
         * @return uint16_t 
         */
        uint16_t getMaxInterval();

        /**
         * @brief Set the Max Interval object
         * 
         * @param interval 
         */
        void setMaxInterval(uint16_t interval);

        /**
         * @brief Get the Mapped Interval object
         * 
         * @return uint8_t 
         */
        uint8_t getMappedInterval();

        /**
         * @brief Get the Mapped Div Interval object
         * 
         * @return uint8_t 
         */
        uint8_t getMappedDivInterval();

        /**
         * @brief Get the Min Interval object
         * 
         * @return uint16_t 
         */
        uint16_t getMinInterval();

        /**
         * @brief Get the Min Interval object
         * 
         * @param interval 
         */
        void setMinInterval(uint16_t interval);

        unsigned long m_now = 0;
        bool m_newInterval = false;
        bool m_newDivInterval = false;
};

#endif
