#include <Arduino.h>

#ifndef STP16_H
#define STP16_H

/**
 * @brief Drives a 16-bit current sink driver / STP16CPC26.
 */
class Stp16
{
    private:
        uint8_t m_csPin;

        void select();

        void deselect();

    public:
};

#endif