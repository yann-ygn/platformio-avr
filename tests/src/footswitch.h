#include <Arduino.h>

#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

/**
 * @brief A footswitch is connected to the µC
 */
class Footswitch
{
    private:
        uint8_t m_pin;

        uint8_t m_debounceTime;
        uint16_t m_longPressTime;
        uint32_t m_now = 0;
        uint32_t m_lastPressTime = 0;

        bool m_switched = false;
        bool m_longPress = false;

        uint8_t m_switchState = 0;
        uint8_t m_lastSwitchState = 0;

    public:
        Footswitch(uint8_t pin, uint8_t dtime, uint16_t lptime) : m_pin(pin), m_debounceTime(dtime), m_longPressTime(lptime) 
        {
            m_lastPressTime = millis();
        };

        void footswitchSetup();

        void footswitchUpdate();
};

#endif