#include <Arduino.h>

#ifndef PROGRAM_H
#define PROGRAM_H

struct program
{
    const uint8_t m_id;
    const uint8_t m_delayEffect;
    const uint16_t m_minInterval;
    const uint16_t m_maxInterval;
    const uint8_t m_tapEnabled;
    const uint8_t m_pot0Enabled;
    const uint8_t m_pot1Enabled;
    const uint8_t m_pot2Enabled;
};

extern program programs[8];

#endif
