#include <Arduino.h>
#include <SPI.h>


#ifndef SWITCHMATRIX_H
#define SWITCHMATRIX_H

class SwitchMatrix
{
    private:
        uint8_t m_csPin;

        uint16_t m_switchArray[16] = { 0 }; // array[y]

        void select();
        void deselect();
    public:
        SwitchMatrix(uint8_t pin) : m_csPin(pin) {}

        void switchMatrixSetup();

        /**
         * @brief Set the Switch Array object
         *
         * @param y Row
         * @param x Column
         * @param value
         */
        void setSwitchArray(uint8_t y, uint8_t x, uint8_t value);
        uint8_t getSwitchArray(uint8_t y, uint8_t x);
        void sendSwitchArray();
};

#endif