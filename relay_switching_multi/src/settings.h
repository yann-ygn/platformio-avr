#include <Arduino.h>

#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
    private:
        uint8_t c_startupStatePin = 4;
        uint8_t c_defaultEffectPin = 3;
        uint8_t c_switchModePin = 2;

        uint8_t m_startupState = 0;
        uint8_t m_defaultEffect = 0;
        uint8_t m_switchMode = 0;

    public:
        void modeSetup();

        uint8_t getStartupState();
        void setStartupState(uint8_t state);

        uint8_t getDefaultEffect();
        void setDefaultEffect(uint8_t effect);

        uint8_t getSwitchMode();
        void setSwitchMode(uint8_t mode);
};

#endif