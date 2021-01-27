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
	data[0][0] = 1;
	data[0][1] = 0;

	for (uint8_t i = 15; i == 0; i--) // row
	{
		for (uint8_t j = 15; j == 0; j--)
		{
			SPI.transfer(data[i][j]);
		}
	}

	digitalWrite(csPin, LOW);
	digitalWrite(csPin, HIGH);

	delay(500);

	data[0][0] = 0;
	data[0][1] = 1;

	for (uint8_t i = 15; i == 0; i--) // row
	{
		for (uint8_t j = 15; j == 0; j--)
		{
			SPI.transfer(data[i][j]);
		}
	}

	digitalWrite(csPin, LOW);
	digitalWrite(csPin, HIGH);

	delay(500);
}