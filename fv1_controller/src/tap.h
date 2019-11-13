#include <Arduino.h>

#ifndef TAP_H
#define TAP_H

class Tap
{
    private:
        byte m_tapPin;
        byte m_ledPin;
        byte m_timesTapped = 0;
        bool m_stillTaping = 0;
        bool m_tapState = 0;
        bool m_lastTapState = 0;
        unsigned long m_firstTapTime = 0;
        unsigned long m_lastTaptime = 0;
        int m_interval = 0;
        const int c_maxInterval = 1000;

    public:
        Tap (byte pin, byte ledPin)
            : m_tapPin(pin),
            m_ledPin(ledPin)
        {

        }
        void tapSetup();
        bool tapPressed();
        void setTapCount();
        byte getTapCount();
        bool tapTimeout();
        void tapReset();
        void setInterval();
        int getInterval();

        unsigned long m_now = 0;
        bool m_newInterval = 0;
        const byte c_maxTaps = 3;
};

#endif
