#include "preset.h"

Loops* Preset::getLoops()
{
    return m_presetLoops;
}

uint8_t Preset::getBank()
{
    return m_bank;
}

uint8_t Preset::getPreset()
{
    return m_preset;
}