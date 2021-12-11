#include "preset.h"

void Preset::presetSetup(uint8_t bank, uint8_t preset, Loops* loops, uint8_t loopscount)
{
    m_bank = bank;
    m_preset = preset;
    m_presetLoops = loops;

    m_presetLoops->setCount(loopscount);
    m_presetLoops->LoopsSetup();
}

uint8_t* Preset::getLoops()
{
    return m_presetLoops->getLoops();
}

uint8_t* Preset::getLoopsStates()
{
    return m_presetLoops->getStates();
}

uint8_t Preset::getBank()
{
    return m_bank;
}

void Preset::setBank(uint8_t bank)
{
    m_bank = bank;
}

uint8_t* Preset::getPreset()
{
    return &m_preset;
}

void Preset::setPreset(uint8_t preset)
{
    m_preset = preset;
}