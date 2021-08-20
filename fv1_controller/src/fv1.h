#include <Arduino.h>

#ifndef FV1_H
#define FV1_H

class FV1
{
    private:
        uint8_t m_p0Pin; // P0 pin #
        uint8_t m_p1Pin; // P1 pin #
        uint8_t m_p2Pin; // P2 pin #
        uint8_t m_s0Pin; // S0 pin #
        uint8_t m_s1Pin; // S1 pin #
        uint8_t m_s2Pin; // S2 pin #

    public:
        /**
         * @brief Construct a new FV1 object
         *
         * @param p0 // P0 pin #
         * @param p1 // P1 pin #
         * @param p2 // P2 pin #
         * @param s0 // S0 pin #
         * @param s1 // S1 pin #
         * @param s2 // S2 pin #
         */
        FV1(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t s0, uint8_t s1, uint8_t s2) :
        m_p0Pin(p0), m_p1Pin(p1), m_p2Pin(p2), m_s0Pin(s0), m_s1Pin(s1), m_s2Pin(s2) { }

        /**
         * @brief Setup the µC's pins
         *
         */
        void FV1Setup();

        /**
         * @brief Sends program changes to the FV1's S0/1/2 inputs
         *
         * @param program
         */
        void sendProgramChange(uint8_t program);

        /**
         * @brief Sends a PWM pulse to the FV1's P0 input
         *
         * @param value
         */
        void sendPot0Value(uint8_t value);

        /**
         * @brief Sends a PWM pulse to the FV1's P1 input
         *
         * @param value
         */
        void sendPot1Value(uint8_t value);

        /**
         * @brief Sends a PWM pulse to the FV1's P2 input
         *
         * @param value
         */
        void sendPot2Value(uint8_t value);
};

#endif