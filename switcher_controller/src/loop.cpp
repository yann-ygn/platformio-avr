#include "loop.h"

uint8_t Loop::getId()
{
    return m_id;
}

void Loop::setId(uint8_t id)
{
    m_id = id;
}

uint8_t Loop::getState()
{
    return m_state;
}

void Loop::setState(uint8_t state)
{
    m_state = state;
}