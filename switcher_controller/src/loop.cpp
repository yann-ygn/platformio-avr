#include "loop.h"

uint8_t Loop::getLoopId()
{
    return m_loopId;
}

uint8_t Loop::getLoopState()
{
    return m_loopState;
}

void Loop::setLoopState(uint8_t state)
{
    m_loopState = state;
}

uint8_t Loop::getLoopOrder()
{
    return m_loopOrder;
}

void Loop::setLoopOrder(uint8_t order)
{
    m_loopOrder = order;
}

uint8_t Loop::getLoopFrom()
{
    return m_loopFrom;
}

void Loop::setLoopFrom(uint8_t from)
{
    m_loopFrom = from;
}

uint8_t Loop::getLoopTo()
{
    return m_loopTo;
}

void Loop::setLoopTo(uint8_t to)
{
    m_loopTo = to;
}