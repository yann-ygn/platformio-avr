#include <Arduino.h>

#ifndef LOOP_H
#define LOOP_H

class Loop
{
    private:
        uint8_t m_id = 0;
        uint8_t m_state = 0;
        uint8_t m_from = 0;
        uint8_t m_to = 0;

    public:
        Loop();
};

#endif