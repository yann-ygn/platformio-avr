#define DEBUG 1

#include <Arduino.h>
#include <SPI.h>
#include "eeprom.h"

void Eeprom::eepromSetup()
{
    pinMode(m_csPin, OUTPUT);
    digitalWrite(m_csPin, HIGH);
	SPI.begin();
}

void Eeprom::select()
{
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
	digitalWrite(m_csPin, LOW);
}

void Eeprom::deselect()
{
    digitalWrite(m_csPin, HIGH);
	SPI.endTransaction();
}

void Eeprom::enableWrite()
{
    select();
	SPI.transfer(WREN);
	deselect();
}

void Eeprom::sendAddress(uint32_t addr) 
{
  	SPI.transfer((uint8_t)(addr>>16));
	SPI.transfer((uint8_t)(addr>>8));
	SPI.transfer((uint8_t)(addr));
}

uint8_t Eeprom::readStatusRegister()
{
	select();
	SPI.transfer(RDSR);
	uint8_t data = SPI.transfer(0x00);
	deselect();
    return data;
}

bool Eeprom::isWip()
{
	uint8_t data = readStatusRegister();
	return (data & (1 << 0));
}

uint8_t Eeprom::readInt8(uint32_t address) 
{
	while (isWip()) {};

	select();
	SPI.transfer(READ);
	sendAddress(address);
	uint8_t data = SPI.transfer(0x00);
	deselect();
	return data;
}

void Eeprom::writeInt8(uint32_t address, uint8_t data)
{
	while (isWip()) {};

	enableWrite();

	select();
	SPI.transfer(WRITE);
	sendAddress(address);
	SPI.transfer(data);
	deselect();
}

uint16_t Eeprom::readInt16(uint32_t address)
{
	while (isWip()) {};

	select();
	SPI.transfer(READ);
	sendAddress(address);
	uint8_t highbyte = SPI.transfer(0x00);
	uint8_t lowbyte = SPI.transfer(0x00);
	deselect();

	return (highbyte << 8) + lowbyte;
}

void Eeprom::writeInt16(uint32_t address, uint16_t data)
{
	while (isWip()) {};

	enableWrite();

	select();
	SPI.transfer(WRITE);
	sendAddress(address);
	SPI.transfer(data >> 8);
	SPI.transfer(data & 0xFF);
	deselect();
}

void Eeprom::readArray(uint32_t address, uint8_t * data, uint8_t length)
{
	while (isWip()) {};

	select();
	SPI.transfer(READ);
	sendAddress(address);
	for(uint8_t i = 0; i < length; i++)
	{
		data[i] = SPI.transfer(0x00);
	}
	deselect();
}

void Eeprom::writeArray(uint32_t address, uint8_t * data, uint8_t length)
{
	while (isWip()) {};

	enableWrite();

	select();
	SPI.transfer(WRITE);
	sendAddress(address);
	for(uint8_t i = 0; i < length; i++)
	{
		SPI.transfer(data[i]);
	}
	deselect();
}

#ifdef DEBUG
	void Eeprom::testInt8()
	{
		for (uint32_t i = 1; i < 20; i++)
		{
			writeInt8(i, 1);
			Serial.print("Reading address : ");
			Serial.print(i);
			Serial.print(" | Value : ");
			Serial.println(readInt8(i));

			delay(500);

			writeInt8(i, 0);
			Serial.print("Reading address : ");
			Serial.print(i);
			Serial.print(" | Value : ");
			Serial.println(readInt8(i));

			delay(500);
		}
	}

	void Eeprom::testInt16()
	{
		writeInt16(985, 1000);
		Serial.print("Reading address : 985");
		Serial.print(" | Value : ");
		Serial.println(readInt16(985));

		delay(500);

		writeInt16(985, 0);
		Serial.print("Reading address : 985");
		Serial.print(" | Value : ");
		Serial.println(readInt16(985));

		delay(500);
	}

	void Eeprom::testArray()
	{
		uint8_t blah1[5] = { 0, 0, 0, 0, 0 };
		uint8_t blah2[5] = { 5, 10, 95, 159, 254 };

		uint8_t result[5] = { };

		writeArray(0, blah1, 5);
		readArray(0, result, 5);
		Serial.println(result[0]);
		Serial.println(result[1]);
		Serial.println(result[2]);
		Serial.println(result[3]);
		Serial.println(result[4]);

		delay(1000); 

		writeArray(0, blah2, 5);
		readArray(0, result, 5);
		Serial.println(result[0]);
		Serial.println(result[1]);
		Serial.println(result[2]);
		Serial.println(result[3]);
		Serial.println(result[4]);

		delay(1000); 
	}
#endif