#include <Arduino.h>

#ifndef TAP_H
#define TAP_H

/**
 * @brief A switch is connected to the µC, and is monitored for press to 
 * calculate the mean value between a defined maximum number of presses. An 
 * LED is flashed at that same frequency.
 */
class Tap
{
    private:
        const byte c_swPin = 53; // Footswitch pin #, to be set.
        const byte c_ledPin = 52; // LED pin #, to be set.
        byte m_timesTapped = 0;
        bool m_tapState = 0;
        bool m_lastTapState = 0;
        unsigned long m_firstTapTime = 0;
        unsigned long m_lastTaptime = 0;
        int m_interval = 0;
        const int c_maxInterval = 1000; // The absolute maximum delay value
        const byte c_debounceTime = 100; // Minimum time between two footswich press

    public:
        /**
         * @brief Setup the µC's pins 
         */
        void tapSetup();

        /**
         * @brief Read the footswitch state
         * 
         * @return true if LOW and if the debounce delay has passed and if its state changed since the last cycle.
         * @return false 
         */
        bool tapPressed();

        /**
         * @brief Check for timeouts
         * 
         * @return true if the tap counter is > 0 and if if the switch hasn't been pressed 
         * in the maximum absolute value * 1.5
         * 
         * @return false 
         */
        bool tapTimeout();

        /**
         * @brief Resets the tap counter 
         */
        void tapReset();

        /**
         * @brief Set the Tap counter
         */
        void setTapCount();

        /**
         * @brief Get the Tap counter
         * @return byte 
         */
        byte getTapCount();

        /**
         * @brief Calculate the mean value between the first and last tap time 
         */
        void setInterval();

        /**
         * @brief Get the current calculated interval
         * 
         * @return int 
         */
        int getInterval();

        unsigned long m_now = 0;
        bool m_newInterval = 0;
        const byte c_maxTaps = 3; // The number of taps before the mean value is calculated
};

#endif
