#include <Arduino.h>

#ifndef LOOPS_H
#define LOOPS_H

/**
 * @brief A loop represents an array oh physical audio loops using input/output jacks, a loop has an id and a state
 *
 */
class Loops
{
    private:
        uint8_t m_loops[16] = {0}; // Loops ID array
        uint8_t m_states[16] = {0}; // Loops states array
        uint8_t m_count = 0; // Number of loops

    public:
        /**
         * @brief Construct a new Loops object
         */
        Loops() {}

        /**
         * @brief Construct a new Loops object
         *
         * @param count Number of loops
         */
        Loops(uint8_t count) :
            m_count(count) {}

        /**
         * @brief Initialize the id and states array according to the loop count
         */
        void LoopsSetup();

        /**
         * @brief Get the Loops object
         *
         * @return uint8_t*
         */
        uint8_t* getLoops();

        /**
         * @brief Get the States object
         *
         * @return uint8_t*
         */
        uint8_t* getStates();

        /**
         * @brief Get the Count object
         *
         * @return uint8_t
         */
        uint8_t getCount();

        /**
         * @brief Set the Count object
         *
         * @param count Number of loops used
         */
        void setCount(uint8_t count);

        /**
         * @brief Set the state of a loop
         *
         * @param loop loop #
         * @param state 1: open | 0 : close
         */
        void setLoopState(uint8_t loop, uint8_t state);

        /**
         * @brief Get the state of a loop
         *
         * @param loop loop #
         * @return uint8_t
         */
        uint8_t getLoopState(uint8_t loop);

        /**
         * @brief Toggle the state of a loop (open/close)
         *
         * @param loop loop #
         */
        void toggleLoopState(uint8_t loop);
};

#endif