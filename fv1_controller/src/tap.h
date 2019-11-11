#include <Arduino.h>

#ifndef TAP_H
#define TAP_H

class Tap
{
    private:
        byte m_pin;
        byte m_ledPin;
        byte m_timesTapped;
        bool m_stillTaping;
        bool m_tapState;
        bool m_lastTapState;
        unsigned long m_firstTapTime;
        unsigned long m_lastTaptime;
        int m_interval;
        const int c_maxInterval = 1000;

    public:
        Tap (byte pin, byte ledPin);
        void tapSetup();
        bool tapPressed();
        void setTapCount();
        byte getTapCount();
        bool tapTimeout();
        void tapReset();
        void setInterval();
        int getInterval();

        unsigned long m_now;
        bool m_newInterval;
        const byte c_maxTaps = 3;
};

#endif
