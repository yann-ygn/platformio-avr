#include "loops.h"

void Loops::loopsSetup()
{
    for (uint8_t i = 0; i < m_loopsCount; i++)
    {
        m_loopsId[i] = i;
        m_loopsState[i] = 0;
    }
}

uint8_t* Loops::getLoopsId()
{
    uint8_t* arr = m_loopsId;
    return arr;
}

uint8_t* Loops::getLoopsState()
{
    uint8_t* arr = m_loopsState;
    return arr;
}

uint8_t Loops::getLoopState(uint8_t loop)
{
    return m_loopsState[loop];
}

void Loops::setLoopState(uint8_t loop, uint8_t state)
{
    m_loopsState[loop] = state;
}

uint8_t* Loops::getLoopsOrder()
{
    uint8_t* arr = m_loopsOrder;
    return arr;
}

uint8_t Loops::getLoopOrder(uint8_t loop)
{
    return m_loopsOrder[loop];
}

uint8_t Loops::getLoopIdByOrder(uint8_t order)
{
    uint8_t returnId = 0;

    for (uint8_t i = 0; i < m_loopsCount; i++)
    {
        if (m_loopsOrder[i] == order)
        {
            returnId =  m_loopsId[i];
            break;
        }
    }

    return returnId;
}

void Loops::setLoopOrder(uint8_t loop, uint8_t order)
{
    m_loopsOrder[loop] = order;
}

uint8_t Loops::getLoopIn(uint8_t loop)
{
    return m_loopsIn[loop];
}

void Loops::setLoopIn(uint8_t loop, uint8_t in)
{
    m_loopsIn[loop] = in;
}

uint8_t Loops::getLoopOut(uint8_t loop)
{
    return m_loopsOut[loop];
}

void Loops::setLoopOut(uint8_t loops, uint8_t out)
{
    m_loopsOut[loops] = out;
}

uint8_t Loops::getLoopsCount()
{
    return m_loopsCount;
}

void Loops::setLoopsCount(uint8_t count)
{
    m_loopsCount = count;
}

void Loops::toggleLoopsState(uint8_t loop)
{
    m_loopsState[loop] = !m_loopsState[loop];
}