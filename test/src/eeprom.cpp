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

void Eeprom::sendAddress(uint8_t addr)
{
	//SPI.transfer((byte)(addr>>16));
	SPI.transfer((byte)(addr>>8));
	SPI.transfer((byte)(addr));
}

bool Eeprom::isWip()
{
	byte data = readStatusRegister();
	return (data & B1);
}

byte Eeprom::readStatusRegister()
{
	select();
	SPI.transfer(RDSR);
	byte data = SPI.transfer(0x00);
	deselect();
    return data;
}

byte Eeprom::readByte(byte addr) 
{
	while (isWip()) {};
	select();
	SPI.transfer(READ);
	sendAddress(addr);
	byte data = SPI.transfer(0x00);
	deselect();
	return data;
}

void Eeprom::writeByte(byte addr, byte data)
{
	while (isWip()) {};
	enableWrite();
	select();
	SPI.transfer(WRITE);
	sendAddress(addr);
	SPI.transfer(data);
	deselect();
}