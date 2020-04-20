#include <Arduino.h>

#include "settings.h"

void Settings::modeSetup()
{
    pinMode(c_startupStatePin, INPUT_PULLUP);
    pinMode(c_defaultEffectPin, INPUT_PULLUP);
    pinMode(c_switchModePin, INPUT_PULLUP);

    m_startupState = digitalRead(c_startupStatePin);
    m_defaultEffect = digitalRead(c_defaultEffectPin);
    m_switchMode = digitalRead(c_switchModePin);
}

uint8_t Settings::getStartupState()
{
    return m_startupState;
}

void Settings::setStartupState(uint8_t state)
{
    m_startupState = state;
}

uint8_t Settings::getDefaultEffect()
{
    return m_defaultEffect;
}

void Settings::setDefaultEffect(uint8_t effect)
{
    m_defaultEffect = effect;
}

uint8_t Settings::getSwitchMode()
{
    return m_switchMode;
}

void Settings::setSwitchMode(uint8_t mode)
{
    m_switchMode = mode;
}