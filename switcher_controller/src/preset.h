#include <Arduino.h>
#include "loops.h"
#include "loop.h"

#ifndef PRESET_H
#define PRESET_H

class Preset
{
    private:
        uint8_t m_bank = 0;
        uint8_t m_preset = 0;
        Loop m_presetLoops[16];
        uint8_t m_presetLoopsCount = 0;
        uint8_t m_presetLoopsId[16] = {0};
        uint8_t* p_presetLoopId = m_presetLoopsId;
        uint8_t m_presetLoopsState[16] = {0};
        uint8_t* p_presetLoopsState = m_presetLoopsState;
        //Loops* m_presetLoops = NULL;

    public:
        Preset() {}
        /**Preset(uint8_t bank, uint8_t preset, Loops* loops) :
            m_bank(bank),
            m_preset(preset),
            m_presetLoops(loops) {}**/

        void presetSetup(uint8_t bank, uint8_t preset, Loops* loops, uint8_t loopscount);

        uint8_t getBank();
        void setBank(uint8_t bank);

        uint8_t* getPreset();
        void setPreset(uint8_t preset);

        uint8_t* getLoops();
        uint8_t* getLoopsStates();

        void setLoopState(uint8_t loop, uint8_t state);
        uint8_t getLoopState(uint8_t loop);
        void toggleLoopState(uint8_t loop);
};

#endif