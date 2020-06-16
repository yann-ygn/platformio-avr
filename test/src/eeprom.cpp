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

#ifdef DEBUG
	void Eeprom::testInt8()
	{
		for (uint32_t i = 256; i < 260; i++)
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
#endif