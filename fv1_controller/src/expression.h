#include <Arduino.h>

#ifndef EXPRESSION_H
#define EXPRESSION_H

/**
 * @brief An expression pedal is plugged into a switched TRS jack with its tip connected to an ADC pin, the switch on the sleeve is connected to another pin.
 * The object is instantiated with both pins numbers, needs to be setup, can check if the pedal is plugged in, if its value changed since the last cycle and return its
 * current value.
 */
class Expr
{
    private:
        uint8_t m_exprPin;
        uint8_t m_checkPin;
        int m_currExprValue = 0;
        int m_lastExprValue = 0;

    public:
        /**
         * @brief Construct a new Expr object.
         * 
         * @param epin 
         * @param cpin 
         */
        Expr(uint8_t epin, uint8_t cpin) : m_exprPin(epin), m_checkPin(cpin)
        {

        };

        /**
         * @brief Setups the µC's pins.
         */
        void exprSetup();

        /**
         * @brief Check if the expression pedal is plugged in.
         * 
         * @return true 
         * @return false 
         */
        bool exprPresent();

        /**
         * @brief Get the Curr Expr Value object.
         * 
         * @return int 
         */
        uint16_t getCurrExprValue();

        /**
         * @brief Get the Mapped Curr Expr Value object
         * 
         * @return uint8_t 
         */
        uint8_t getMappedCurrExprValue();

        /**
         * @brief Checks if the expression pedal moved.
         * 
         * @return true 
         * @return false 
         */
        bool exprTurned();
};

#endif