#include "preset.h"

void Preset::presetSetup(uint8_t bank, uint8_t preset, Loops* loops, uint8_t loopscount)
{
    m_bank = bank;
    m_preset = preset;
    m_presetLoops = loops;

    m_presetLoops->setLoopsCount(loopscount);
    m_presetLoops->loopsSetup();
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

uint8_t* Preset::getPresetLoopsId()
{
    return m_presetLoops->getLoopsId();
}

uint8_t* Preset::getPresetLoopsStates()
{
    return m_presetLoops->getLoopsState();
}

uint8_t* Preset::getPresetLoopsOrder()
{
    return m_presetLoops->getLoopsOrder();
}

void Preset::swapPresetLoopsOrder(uint8_t id1, uint8_t order1, uint8_t id2, uint8_t order2)
{
    m_presetLoops->setLoopOrder(id1, order2);
    m_presetLoops->setLoopOrder(id2, order1);
}

uint8_t Preset::getPresetLoopIdByOrder(uint8_t order)
{
    return m_presetLoops->getLoopIdByOrder(order);
}

void Preset::setPresetLoopSendReturn(uint8_t loop, uint8_t send, uint8_t ret)
{
    m_presetLoops->setLoopSend(loop, send);
    m_presetLoops->setLoopReturn(loop, ret);
}

void Preset::setLoopState(uint8_t loop, uint8_t state)
{
    m_presetLoops->setLoopState(loop, state);
}

uint8_t Preset::getLoopState(uint8_t loop)
{
    return m_presetLoops->getLoopState(loop);
}

void Preset::toggleLoopState(uint8_t loop)
{
    m_presetLoops->toggleLoopsState(loop);
}