#include <Arduino.h>
#include <SPI.h>

uint8_t csPin = 49;
uint16_t data[16] = {0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF};

void setup() 
{
	pinMode(csPin, OUTPUT);
	digitalWrite(csPin, HIGH);
	delay(1000);
	
	SPI.begin();
}

void loop()
{
	SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

	for (int16_t y = 15; y >= 0; y--) {
        SPI.transfer16(data[y]);
    }
    SPI.endTransaction();
}