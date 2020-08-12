#include <Arduino.h>

#include "program.h"

program programs[8] =
{
    //programs[0] : simple digital delay
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 100,
        .m_maxInterval = 1000,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[1] : dark digital delay
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 100,
        .m_maxInterval = 1000,
        .m_tapEnabled = 0,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[2] : modulated digital delay
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 480,
        .m_maxInterval = 960,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[3] : 
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[4] : 
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[5] : 
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[6] : 
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
    //programs[7] : 
    {
        .m_id = 0,
        .m_delayEffect = 1,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = 1,
        .m_pot0Enabled = 1,
        .m_pot1Enabled = 1,
        .m_pot2Enabled = 1
    },
};