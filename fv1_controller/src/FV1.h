#include <Arduino.h>

#ifndef FV1_H
#define FV1_H

class FV1
{
    private:
        const uint8_t c_latchPin = 0; // Latch pin for the shift register, to be set
        const uint8_t c_pot0Pin = 0;
        const uint8_t c_pot1Pin = 0;
        const uint8_t c_pot2Pin = 0;

    public:
        void sendProgramChange(uint8_t program);

        void sendPot0Value(int value);

        void sendPot1Value(int value);

        void sendPot2Value(int value);

};

#endif