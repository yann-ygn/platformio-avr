#include <Arduino.h>

#ifndef LOOP_H
#define LOOP_H

class Loop
{
    private:
        uint8_t m_loopId = 0;
        uint8_t m_loopState = 0;
        uint8_t m_loopOrder = 0;
        uint8_t m_loopFrom = 0;
        uint8_t m_loopTo = 0;

    public:
        Loop();

        uint8_t getLoopId();

        uint8_t getLoopState();
        void setLoopState(uint8_t state);

        uint8_t getLoopOrder();
        void setLoopOrder(uint8_t order);

        uint8_t getLoopFrom();
        void setLoopFrom(uint8_t from);

        uint8_t getLoopTo();
        void setLoopTo(uint8_t to);
};

#endif