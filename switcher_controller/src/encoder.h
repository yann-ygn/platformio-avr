#include <Arduino.h>

#ifndef ENCODER_H
#define ENCODER_H

const uint8_t c_encoderIncrement = 0x20;
const uint8_t c_encoderDrecrement = 0x10;

/**
 * @brief Read the state of an encoder and increments/decrements a counter in regards to a set max/min value
 */
class Encoder
{
    private:
        uint8_t m_encoderPinA; // Encoder CLK pin #
        uint8_t m_encoderPinB; // Encoder DT pin #
        uint8_t m_minCounterValue; // Min counter value
        uint8_t m_maxCounterValue; // Max counter value
        uint8_t m_counter = 0; // Encoder counter
        uint8_t m_encoderState = 0;
        uint8_t m_lastEncoderState = 0;
        const uint8_t c_encoderStates[7][4] =
        {
            {0x0, 0x2, 0x4, 0x0},
            {0x3, 0x0, 0x1, 0x0 | 0x10},
            {0x3, 0x2, 0x0, 0x0},
            {0x3, 0x2, 0x1, 0x0},
            {0x6, 0x0, 0x4, 0x0},
            {0x6, 0x5, 0x0, 0x0 | 0x20},
            {0x6, 0x5, 0x4, 0x0},
        };

        /**
         * @brief Read the current state of the encoder
         *
         * @return uint8_t
         */
        uint8_t readEncoderState();

    public:
        /**
         * @brief Construct a new Encoder object
         *
         * @param pina // Encoder CLK pin #
         * @param pinb // Encoder DT pin #
         * @param minvalue // Min counter value
         * @param maxvalue // Max counter value
         */
        Encoder (uint8_t pina, uint8_t pinb, uint8_t minvalue, uint8_t maxvalue) :
            m_encoderPinA(pina),
            m_encoderPinB(pinb),
            m_minCounterValue(minvalue),
            m_maxCounterValue(maxvalue) {}

        /**
         * @brief Construct a new Encoder object without setting the counter values
         *
         * @param pina // Encoder CLK pin #
         * @param pinb // Encoder DT pin #
         */
        Encoder (uint8_t pina, uint8_t pinb) :
            m_encoderPinA(pina),
            m_encoderPinB(pinb),
            m_minCounterValue(0),
            m_maxCounterValue(1) {}

        /**
         * @brief Setup the µC's pins
         */
        void encoderSetup();

        /**
         * @brief Monitor the encoder for turns and manage the counter
         *
         * @return true
         * @return false
         */
        bool encoderPoll();

        /**
         * @brief Get the Counter object
         *
         * @return uint8_t
         */
        uint8_t getCounter();

        /**
         * @brief Set the Counter object
         *
         * @param counter
         */
        void setCounter(uint8_t counter);

        /**
         * @brief Get the Min Value object
         *
         * @return uint8_t
         */
        uint8_t getMinCounterValue();

        /**
         * @brief Get the Max Value object
         *
         * @return uint8_t
         */
        uint8_t getMaxCounterValue();

        /**
         * @brief Set the Min Counter Value object
         *
         * @param value
         */
        void setMinCounterValue(uint8_t value);

        /**
         * @brief Set the Max Counter Value object
         *
         * @param value
         */
        void setMaxCounterValue(uint8_t value);

        /**
         * @brief Get the Encoder State object
         *
         * @return uint8_t 0x10 = Decrement | 0x20 : Increment
         */
        uint8_t getEncoderState();
};

#endif