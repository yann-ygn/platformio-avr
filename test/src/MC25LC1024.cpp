// MC25LC1024 library for Arduino
// initial release by Sylvain GARNAVAULT - 2014/07/09

#include "MC25LC1024.h"

////////////////////////
//     INITIATION     //
////////////////////////

MC25LC1024::MC25LC1024(byte pin) {
	_cs = pin;                              // choose the chip select pin
	pinMode(_cs,OUTPUT);                    // set the pin as output
    digitalWrite(_cs,HIGH);                 // set the pin to default HIGH state
    
    //TODO CHANGER ÇA
    SPI.setBitOrder(MSBFIRST);              // the chip works MSB first
    //SPI.setFrequency(20000000);    			// transmission as fast as possible
    SPI.setDataMode(SPI_MODE0);             // clock MODE0 : rising edge, low default state
    SPI.begin();                            // initiate SPI
    }

/////////////////////////
//  PRIVATE METHODS    //
/////////////////////////

void MC25LC1024::enableWrite() {
	digitalWrite(_cs,LOW);              // select CHIP
	SPI.transfer(WREN);                 // send WREN command
	digitalWrite(_cs,HIGH);             // end transmission
    }

void MC25LC1024::sendAddress(long addr) {
	SPI.transfer((byte)(addr>>16));     // MSB with 7 first bits beeing don't care bits
	SPI.transfer((byte)(addr>>8));      // MSB
	SPI.transfer((byte)(addr));         // LSB
	}

bool MC25LC1024::WIP() {
	byte data = readStatus();           // get data byte
	return (data & B1);                 // return data
	}

/////////////////////////
//  PRIVATE METHODS    //
/////////////////////////


void MC25LC1024::writeByte(long addr, byte data) {
	enableWrite();                      // enable write
	digitalWrite(_cs,LOW);              // select CHIP
	SPI.transfer(WRITE);                // send WRITE command
	sendAddress(addr);                  // send address
	SPI.transfer(data);                 // transfer data
	digitalWrite(_cs,HIGH);             // end transmission
	while (WIP()) {};                   // wait for writing finish
	}

void MC25LC1024::writeArray(long addr, byte* data, int length) {
	enableWrite();                      // enable write
	digitalWrite(_cs,LOW);              // select chip
	SPI.transfer(WRITE);                // send WRITE command
	sendAddress(addr);                  // send address
	for (int i=0; i<length; i++) {
		SPI.transfer(data[i]);          // transfer data
		}
	digitalWrite(_cs,HIGH);             // release chip, signal end transfer
	while (WIP()) {};                   // wait for writing finish
	}

byte MC25LC1024::readByte(long addr) {
	digitalWrite(_cs,LOW);              // select chip
	SPI.transfer(READ);                 // send READ command
	sendAddress(addr);                  // send address
	byte data = SPI.transfer(0x00);     // get data byte
	digitalWrite(_cs,HIGH);             // release chip, signal end transfer
	return data;
	}

void MC25LC1024::readArray(long addr, byte *data, int length) {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(READ); 				// send READ command
	sendAddress(addr);					// send address
	for (int i=0; i<length; i++) {
		data[i] = SPI.transfer(0x00);	// get data byte
		}
	digitalWrite(_cs,HIGH);				// release chip, signal end transfer
	}

byte MC25LC1024::readStatus() {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(RDSR); 				// send RDSR command
	byte data = SPI.transfer(0x00);     // get status register
	digitalWrite(_cs,HIGH);				// end transmission
    return data;                        // return status register
    }

void MC25LC1024::writeStatus(byte data) {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(WRSR); 				// send WRSR command
	SPI.transfer(data);                 // send status register
	digitalWrite(_cs,HIGH);				// end transmission
    }

void MC25LC1024::pageErase(long addr) {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(PE);                   // send PE command
	sendAddress(addr);                  // send addres
	digitalWrite(_cs,HIGH);				// end transmission
	while (WIP()) {};                   // wait for writing finish
    }

void MC25LC1024::sectorErase(long addr) {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(SE);                   // send SE command
	sendAddress(addr);                  // send addres
	digitalWrite(_cs,HIGH);				// end transmission
	while (WIP()) {};                   // wait for writing finish
    }

void MC25LC1024::chipErase() {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(CE);                   // send CE command
	digitalWrite(_cs,HIGH);				// end transmission
	while (WIP()) {};                   // wait for writing finish
    }

void MC25LC1024::deepPowerDown() {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(DPD);                  // send DPD command
	digitalWrite(_cs,HIGH);				// end transmission
    }

byte MC25LC1024::releasePowerDown() {
	digitalWrite(_cs,LOW);				// select chip
	SPI.transfer(RDID);                 // send RDID command
    sendAddress(0);                     // send dummy address
	byte data=SPI.transfer(0x00);       // get signature
    digitalWrite(_cs,HIGH);				// end transmission
    return data;                        // return signature
    }