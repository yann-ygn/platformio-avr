#include <Arduino.h>

#ifndef BYPASS_H
#define BYPASS_H

class Bypass
{
    private:
        byte m_relayPin;
        byte m_ledPin;
        byte m_okPin;
        byte m_switchPin;
        byte m_startupPin;
        unsigned long m_lastPressTime = 0;
        byte m_switchState = 0;
        byte m_lastSwtichState = 0;
        byte m_relayState = 0;
        const unsigned int c_debounceTime = 300;

    public:
        Bypass(byte relayPin, byte ledPin, byte okPin, byte switchPin, byte startupPin) : 
            m_relayPin(relayPin),
            m_ledPin(ledPin),
            m_okPin(okPin),
            m_switchPin(switchPin),
            m_startupPin(startupPin)
        {

        }
        void bypassSetup();
        boolean bypassPressed();
        void switchRelay();
        unsigned long m_now = 0;
};

#endif