#include <Arduino.h>
#include "encoder.h"

#ifndef HARDWARE_H
#define HARDWARE_H

class Hardware
{
    private:
        // Hardware Triggers
        bool m_selectorMove = false;
        bool m_selectorSwitchPress = false;
        bool m_selectorSwitchLongPress = false;
        bool m_editSwitchPress = false;
        bool m_editSwitchLongPress = false;

        // Menu States
        bool m_presetMenuDisplay = false;
        bool m_mainMenuDisplay = false;
        bool m_editMenuDisplay = false;
        bool m_loopEditMenuDisplay = false;

    public:
        void hardwareSetup();
        void hardwarePoll();
        void resetHardwareTriggers();

        bool getSelectorMove();
        bool getSelectorwitchPress();
        bool getSelectorSwitchLongPress();
        bool getEditSwitchPress();
        bool getEditSwitchLongPress();
};

#endif