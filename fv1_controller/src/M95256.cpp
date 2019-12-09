#include <SPI.h>

#include "M95256.h"


void M95256::setup()
{	
	pinMode(m_csPin,OUTPUT);
    digitalWrite(m_csPin,HIGH);
	SPI.begin();
}

void M95256::select()
{
	SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
	digitalWrite(m_csPin,LOW);
}

void M95256::deselect()
{
	digitalWrite(m_csPin,HIGH);
	SPI.endTransaction();
}

void M95256::enableWrite()
{
	select();
	SPI.transfer(WREN);
	deselect();
}

void M95256::sendAddress(long addr)
{
	SPI.transfer((byte)(addr>>16));
	SPI.transfer((byte)(addr>>8));
	SPI.transfer((byte)(addr));
}

bool M95256::WIP()
{
	byte data = readStatus();
	return (data & B1);
}

byte M95256::readStatus()
{
	select();
	SPI.transfer(RDSR);
	byte data = SPI.transfer(0x00);
	deselect();
    return data;
}

void M95256::writeByte(byte addr, byte data)
{
	while (WIP()) {};
	enableWrite();
	select();
	SPI.transfer(WRITE);
	sendAddress(addr);
	SPI.transfer(data);
	deselect();
}

void M95256::writeArray(byte addr, byte* data, int length)
{
	enableWrite();
	select();
	digitalWrite(m_csPin,LOW);
	SPI.transfer(WRITE);
	sendAddress(addr);
	for (int i=0; i<length; i++)
	{
		SPI.transfer(data[i]);
	}
	while (WIP()) {};
	deselect();
}

byte M95256::readByte(byte addr) 
{
	while (WIP()) {};
	select();
	SPI.transfer(READ);
	sendAddress(addr);
	byte data = SPI.transfer(0x00);
	deselect();
	return data;
}

void M95256::readArray(byte addr, byte *data, int length)
{
	select();
	SPI.transfer(READ);
	sendAddress(addr);
	for (int i=0; i<length; i++)
	{
		data[i] = SPI.transfer(0x00);
	}
	deselect();
}
