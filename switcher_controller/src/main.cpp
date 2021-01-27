#include <Arduino.h>
#include <SPI.h>

uint8_t csPin = 49;
uint8_t data[16][16] = {};

void setup() 
{
	pinMode(csPin, OUTPUT);
	digitalWrite(csPin, HIGH);
}

void loop() {
	SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

}