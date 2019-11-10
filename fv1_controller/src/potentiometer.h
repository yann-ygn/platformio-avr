#include <Arduino.h>

#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Pot
{
    private:
        byte m_pin;
        int m_currPotValue;
        int m_lastPotValue;
        int readPotValue();

    public:
        Pot(byte pin);
        void potSetup();
        int getPotValue();
        bool potTurned();
};

#endif