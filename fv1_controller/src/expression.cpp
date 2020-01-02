#define DEBUG 1

#include <Arduino.h>

#include "expression.h"

void Expr::exprSetup()
{
    pinMode(m_exprPin, INPUT);
    pinMode(m_checkPin, INPUT_PULLUP);
}

bool Expr::exprPresent()
{
    uint8_t state = digitalRead(m_checkPin);

    if (state)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int Expr::getCurrExprValue()
{
    return m_currExprValue;
}

bool Expr::exprTurned()
{
    m_currExprValue = analogRead(m_exprPin);

    if (abs(m_currExprValue - m_lastExprValue) > 3)
    {
        #ifdef DEBUG
            Serial.print("Expression pedal : ");
            Serial.println(m_currExprValue);
        #endif

        m_lastExprValue = m_currExprValue;
        return true;
    }
    else
    {
        return false;
    }
}