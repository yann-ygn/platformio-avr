#include <Arduino.h>
#include "loops.h"

#ifndef PRESET_H
#define PRESET_H

class Preset
{
    private:
        uint8_t m_bank;
        uint8_t m_preset;
        Loops* m_presetLoops;

    public:
        Preset(uint8_t bank, uint8_t preset, Loops* loops) :
            m_bank(bank),
            m_preset(preset),
            m_presetLoops(loops) {}

        uint8_t getBank();
        uint8_t getPreset();
        Loops* getLoops();
};

#endif