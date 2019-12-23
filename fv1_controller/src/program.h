#include <Arduino.h>

#ifndef PROGRAM_H
#define PROGRAM_H

struct program
{
    uint8_t m_id;
    uint8_t m_isDelay;
    int m_maxInterval;
    uint8_t m_tapEnabled;
    uint8_t m_pot0Enabled;
    uint8_t m_pot1Enabled;
    uint8_t m_pot2Enabled;
};

#endif
