#include "debug.h"

void initLog()
{
    Serial.println(RESET);
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
}