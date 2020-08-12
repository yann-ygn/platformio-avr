#include <Arduino.h>

#include "programs.h"

program programs[8] =
{
    //programs[0] : simple digital delay
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 100,
        .m_maxInterval = 1000,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[1] : dark digital delay
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 100,
        .m_maxInterval = 1000,
        .m_tapEnabled = 0,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[2] : modulated digital delay
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 480,
        .m_maxInterval = 960,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[3] : 
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[4] : 
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[5] : 
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[6] : 
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
    //programs[7] : 
    {
        .m_id = 0,
        .m_delayEffect = true,
        .m_minInterval = 0,
        .m_maxInterval = 1000,
        .m_tapEnabled = true,
        .m_pot0Enabled = true,
        .m_pot1Enabled = true,
        .m_pot2Enabled = true,
        .m_pot3Enabled = true
    },
};