#define DEBUG 1

#include "switchmatrix.h"

void SwitchMatrix::select()
{
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    digitalWrite(m_csPin, HIGH);
}

void SwitchMatrix::deselect()
{
    digitalWrite(m_csPin, LOW);
    digitalWrite(m_csPin, HIGH);
    SPI.endTransaction();
}

void SwitchMatrix::switchMatrixSetup()
{
    pinMode(m_csPin, OUTPUT);
    digitalWrite(m_csPin, HIGH);

    SPI.begin();
}

void SwitchMatrix::setSwitchArray(uint8_t y, uint8_t x, uint8_t value)
{
    #ifdef DEBUG
        Serial.print("Connecting Y : ");
        Serial.print(y);
        Serial.print(" to X : ");
        Serial.println(x);
    #endif

    bitWrite(m_switchArray[y], x, value);
}

uint8_t SwitchMatrix::getSwitchArray(uint8_t y, uint8_t x)
{
    return bitRead(m_switchArray[y], x);
}

void SwitchMatrix::sendSwitchArray()
{
    select();

    for (int y = 15; y >= 0; y--) // Rows
    {
        SPI.transfer16(m_switchArray[y]);
    }

    deselect();
}