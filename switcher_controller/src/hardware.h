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