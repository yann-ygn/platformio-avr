#include <Arduino.h>

#ifndef LOOP_H
#define LOOP_H

class Loop
{
    private:
        uint8_t m_id;
        uint8_t m_state;

    public:
        Loop(uint8_t id, uint8_t state) :
            m_id(id),
            m_state(state) {}

        uint8_t getId();
        void setId(uint8_t id);
        uint8_t getState();
        void setState(uint8_t state);
};

#endif