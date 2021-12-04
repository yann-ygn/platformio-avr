#include "loops.h"

void Loops::LoopsSetup()
{
    for (uint8_t i = 0; i < m_count; i++)
    {
        m_loops[i] = i;
        m_states[i] = 0;
    }
}

uint8_t* Loops::getLoops()
{
    uint8_t* arr = m_loops;
    return arr;
}

uint8_t* Loops::getStates()
{
    uint8_t* arr = m_states;
    return arr;
}

uint8_t Loops::getCount()
{
    return m_count;
}

void Loops::setCount(uint8_t count)
{
    m_count = count;
}

uint8_t Loops::getLoopState(uint8_t loop)
{
    return m_states[loop];
}

void Loops::setLoopState(uint8_t loop, uint8_t state)
{
    m_states[loop] = state;
}

void Loops::toggleLoopState(uint8_t loop)
{
    m_states[loop] = !m_states[loop];
}