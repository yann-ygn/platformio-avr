#include <Arduino.h>
#include "menu.h"
#include "encoder.h"
#include "led.h"
#include "switch.h"
#include "preset.h"
#include "memory.h"
#include "leddriver.h"

#ifndef HARDWARE_H
#define HARDWARE_H

const uint8_t c_firstBank = 65; // A
const uint8_t c_maxBanks = 10;
const uint8_t c_firstPreset = 0;
const uint8_t c_maxPresets = 4;
const uint8_t c_firstLoop = 0;
const uint8_t c_maxLoops = 6;

class Hardware
{
    private:
        // Hardware Triggers
        bool m_selectorMove = false;
        bool m_selectorSwitchPress = false;
        bool m_selectorSwitchLongPress = false;
        bool m_editSwitchPress = false;
        bool m_editSwitchLongPress = false;
        bool m_presetUpFswPress = false;
        bool m_presetUpFswLongPress = false;
        bool m_presetDownFswPress = false;
        bool m_presetDownFswLongPress = false;
        bool m_preset1FswPress = false;
        bool m_preset2FswPress = false;
        bool m_preset3FswPress = false;
        bool m_preset4FswPress = false;

        // Menu States
        bool m_presetMenuDisplay = false;
        bool m_presetEditMenuDisplay = false;
        bool m_presetLoopEditMenuDisplay = false;
        bool m_mainMenuDisplay = false;

        // Presets logic
        uint8_t m_currentPresetBank = 0;
        uint8_t m_currentPreset = 0;
        Preset *p_currentPreset = NULL;

    public:
        void hardwareSetup();
        void hardwarePoll();
        void hardwareStartup();
        void restoreLastState();
        void resetHardwareTriggers();

        void menuSetup();

        void loadPresetBank();

        bool getSelectorMove();
        bool getSelectorwitchPress();
        bool getSelectorSwitchLongPress();
        bool getEditSwitchPress();
        bool getEditSwitchLongPress();

        bool getPresetMenuDisplay();
        bool getPresetEditMenuDisplay();
        bool getPresetLoopEditMenuDisplay();
        bool getMainMenuDisplay();
};

#endif