#include <Arduino.h>

#ifndef PROGRAM_H
#define PROGRAM_H

struct program
{
    const uint8_t m_id;
    const bool m_delayEffect;
    const uint16_t m_minInterval;
    const uint16_t m_maxInterval;
    const bool m_tapEnabled;
    const bool m_pot0Enabled;
    const bool m_pot1Enabled;
    const bool m_pot2Enabled;
};

extern program programs[8];

#endif
