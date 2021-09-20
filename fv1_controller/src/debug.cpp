#include "debug.h"

void logAction(uint8_t periph, uint8_t periphPinNumber, String message[10], uint8_t messageColor)
{
    Serial.print(BLUE);
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] | ");

    Serial.print(CYAN);
    Serial.print("ACTION | ");

    switch (periph)
    {
    case 1:
        /* code */
        break;

    default:
        break;
    }
}