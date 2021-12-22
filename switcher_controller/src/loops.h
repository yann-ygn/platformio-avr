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
        uint8_t m_loopsId[16] = {0}; // Loops ID array
        uint8_t m_loopsState[16] = {0}; // Loops states array
        uint8_t m_loopsOrder[16] = {0};
        uint8_t m_loopsIn[16] = {0};
        uint8_t m_loopsOut[16] = {0};
        uint8_t m_loopsCount = 0; // Number of loops

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
            m_loopsCount(count) {}

        /**
         * @brief Initialize the id and states array according to the loop count
         */
        void loopsSetup();

        /**
         * @brief Get the Loops object
         *
         * @return uint8_t*
         */
        uint8_t* getLoopsId();

        /**
         * @brief Get the States object
         *
         * @return uint8_t*
         */
        uint8_t* getLoopsState();

        /**
         * @brief Get the state of a loop
         *
         * @param loop loop #
         * @return uint8_t
         */
        uint8_t getLoopState(uint8_t loop);

        /**
         * @brief Set the state of a loop
         *
         * @param loop loop #
         * @param state 1: open | 0 : close
         */
        void setLoopState(uint8_t loop, uint8_t state);

        uint8_t* getLoopsOrder();

        uint8_t getLoopOrder(uint8_t loop);

        void setLoopOrder(uint8_t loop, uint8_t order);

        uint8_t getLoopIn(uint8_t loop);

        void setLoopIn(uint8_t loop, uint8_t in);

        uint8_t getLoopOut(uint8_t loop);

        void setLoopOut(uint8_t loop, uint8_t out);

        /**
         * @brief Get the Count object
         *
         * @return uint8_t
         */
        uint8_t getLoopsCount();

        /**
         * @brief Set the Count object
         *
         * @param count Number of loops used
         */
        void setLoopsCount(uint8_t count);

        /**
         * @brief Toggle the state of a loop (open/close)
         *
         * @param loop loop #
         */
        void toggleLoopsState(uint8_t loop);
};

#endif