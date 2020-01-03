#include <Arduino.h>

#ifndef FV1_H
#define FV1_H

class FV1
{
    private:
        const uint8_t c_latchPin = 16; // Latch pin for the shift register, to be set
        const uint8_t c_pot0Pin = 12; // PWM pin connected to the P0 input, to be set
        const uint8_t c_pot1Pin = 13; // PWM pin connected to the P1 input, to be set
        const uint8_t c_pot2Pin = 14; // PWM pin connected to the P2 input, to be set

    public:
        void FV1Setup();

        void sendProgramChange(uint8_t program);

        void sendPot0Value(int value);

        void sendPot1Value(int value);

        void sendPot2Value(int value);
};

#endif