#include "debug.h"

void initLog()
{
    Serial.print(RESET);
    Serial.println("LOG RESET");
}

void test()
{
    Serial.print(WHITE);
    Serial.print("WHITE ");
    Serial.print(RED);
    Serial.print("RED ");
    Serial.print(GREEN);
    Serial.print("GREEN ");
    Serial.print(YELLOW);
    Serial.print("YELLOW ");
    Serial.print(BLUE);
    Serial.print("BLUE ");
    Serial.print(MAGENTA);
    Serial.print("MAGENTA ");
    Serial.print(CYAN);
    Serial.print("CYAN ");
    Serial.print(RESET);
    Serial.print("RESET ");
    Serial.print(BLUE);
    Serial.print(millis());
    Serial.print(RESET);
    Serial.print(" | ");
    Serial.print(YELLOW);
    Serial.print("SWITCH");
}

void logSwitchAction(uint8_t periph, uint8_t action)
{
    Serial.print(CYAN);
    Serial.print(millis());
    Serial.print(RESET);
    Serial.print(" | ");
    Serial.print(YELLOW);
    Serial.print("SWITCH");
}