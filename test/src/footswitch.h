#include <Arduino.h>

#ifndef FOOTSWITCH_H
#define FOOTSWITCH_H

class Footswitch
{
    private:
        uint8_t m_pin;

        uint8_t m_footswitchState = 0;
        uint8_t m_rawState = 0;
        uint8_t m_lastFootswithState = 0;
        uint8_t m_deglitchedState = 0;
        uint8_t m_debouncedState = 1;

        uint32_t m_now = 0;
        uint32_t m_deglitchTime = 0;
        uint32_t m_lastSwitchedTime = 0;
        uint32_t m_lastPushedTime = 0;
        const uint8_t m_deglitchPeriod = 30;
        const uint8_t m_debouncePeriod = 50;
        uint16_t m_longPressPeriod;

        uint8_t m_footswitchSwitched = 0;
        uint8_t m_footswitchLongPress = 0;
        uint8_t m_longPressActive = 0;


    public:
        Footswitch(uint8_t pin, uint16_t lpperiod) : m_pin(pin), m_longPressPeriod(lpperiod)
        {

        };

        void footswitchSetup();

        void footswitchPoll();

        bool footswitchSwitched();

        bool footswitchOn();

        bool footswitchPushed();

        bool footswitchReleased();

        bool footswitchLongPress();
};

#endif
