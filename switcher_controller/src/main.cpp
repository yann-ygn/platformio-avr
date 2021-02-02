#include <Arduino.h>
#include <SPI.h>

uint8_t csPin = 1;
uint16_t data[16] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

void setup() 
{
	pinMode(csPin, OUTPUT);
	digitalWrite(csPin, HIGH);
	delay(1000);

	SPI.begin();

	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

	for (int16_t y = 15; y >= 0; y--) {
        SPI.transfer16(data[y]);
    }
    SPI.endTransaction();
	
    delayMicroseconds(8);
    digitalWrite(csPin, LOW);
    delayMicroseconds(8);
    digitalWrite(csPin, HIGH);
}

void loop()
{
	
}