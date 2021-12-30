#include <Arduino.h>
#include "menu.h"
#include "encoder.h"
#include "led.h"
#include "switch.h"
#include "preset.h"
#include "memory.h"
#include "leddriver.h"
#include "switchmatrix.h"

#ifndef HARDWARE_H
#define HARDWARE_H

const uint8_t c_firstPresetBank = 65; // A
const uint8_t c_maxPresetBanks = 10;
const uint8_t c_firstPreset = 48; // 0
const uint8_t c_maxPresets = 4;
const uint8_t c_firstLoop = 0;
const uint8_t c_maxLoops = 8;

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
        bool m_preset0FswPress = false;
        bool m_preset1FswPress = false;
        bool m_preset2FswPress = false;
        bool m_preset3FswPress = false;

        // Loops Ins/Outs
        const uint8_t c_inputLoopReturn = 0; // X0
        const uint8_t c_tunerLoopSend = 15; // Y15
        const uint8_t c_buffer1LoopSend = 14; // Y14
        const uint8_t c_buffer1LoopReturn = 1; // X1
        const uint8_t c_buffer2LoopSend = 13; // Y13
        const uint8_t c_buffer2LoopReturn = 2; // X1
        const uint8_t c_outputLoopSend = 0; // Y0;

        // Menu States
        bool m_presetMenuDisplay = false;
        bool m_presetEditMenuDisplay = false;
        bool m_presetEditSwapLoopDisplay = false;
        bool m_presetLoopEditMenuDisplay = false;
        bool m_mainMenuDisplay = false;
        Menu *p_currentMenu = NULL;

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

        void processSelector();
        void processSelectorSwitchPress();
        void processSelectorSwitchLongPress();

        void setupMatrixLoops();
        void processMatrixLoops();

        void menuSetup();
        void resetMenuStates();
        void displayPresetMenu();
        void displayPresetEditMenu();

        void loadPresetBank();
        void loadPreset();
        void savePreset();

        bool getSelectorMove();
        bool getSelectorwitchPress();
        bool getSelectorSwitchLongPress();
        bool getEditSwitchPress();
        bool getEditSwitchLongPress();
        bool getPresetUpFswPress();
        bool getPresetDownFswPress();
        bool getPreset0FswPress();
        bool getPreset1FswPress();
        bool getPreset2FswPress();
        bool getPreset3FswPress();

        bool getPresetMenuDisplay();
        bool getPresetEditMenuDisplay();
        bool getPresetLoopEditMenuDisplay();
        bool getMainMenuDisplay();
};

#endif