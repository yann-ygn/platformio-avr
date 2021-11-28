#include <Arduino.h>

#ifndef LOOPS_H
#define LOOPS_H

class Loops
{
    private:
        uint8_t m_loops[16] = {0};
        uint8_t m_states[16] = {0};
        uint8_t m_count;

    public:
        Loops(uint8_t count) :
            m_count(count) {}

        void LoopsSetup();

        uint8_t* getLoops();
        uint8_t* getStates();
        uint8_t getCount();

        void setLoopState(uint8_t loop, uint8_t state);
        uint8_t getLoopState(uint8_t loop);
        void toggleLoopState(uint8_t loop);
};

#endif