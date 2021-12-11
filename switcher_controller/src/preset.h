#include <Arduino.h>
#include "loops.h"

#ifndef PRESET_H
#define PRESET_H

class Preset
{
    private:
        uint8_t m_bank = 0;
        uint8_t m_preset = 0;
        Loops* m_presetLoops = NULL;

    public:
        Preset() {}
        Preset(uint8_t bank, uint8_t preset, Loops* loops) :
            m_bank(bank),
            m_preset(preset),
            m_presetLoops(loops) {}

        void presetSetup(uint8_t bank, uint8_t preset, Loops* loops, uint8_t loopscount);

        uint8_t getBank();
        void setBank(uint8_t bank);

        uint8_t* getPreset();
        void setPreset(uint8_t preset);

        uint8_t* getLoops();
        uint8_t* getLoopsStates();
};

#endif