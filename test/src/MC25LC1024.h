// MC25LC1024 library for Arduino
// initial release by Sylvain GARNAVAULT - 2014/07/09

#ifndef MC25LC1024_h

	#define MC25LC1024_h
	
	#include "Arduino.h"        // include arduino Core
    #include "SPI.h"            // include SPI library

    #define READ  B00000011     // read byte
    #define WRITE B00000010     // write byte
	#define WREN  B00000110     // write enable
	#define WRDI  B00000100     // write disable
	#define RDSR  B00000101     // read status register
	#define WRSR  B00000001     // write status register
    #define PE    B01000010     // page erase
    #define SE    B11011000     // sector erase
    #define CE    B11000111     // chip erase
    #define RDID  B10101011     // release from Deep power-down and read electronic signature
    #define DPD   B10111001     // deep power-down mode

	class MC25LC1024 {
		public:
			MC25LC1024(byte pin);                                      // initiate objet
			void writeByte(long addr, byte data);                     // write byte
			void writeArray(long addr, byte data[], int length);       // write array
        
			byte readByte(long addr);                                 // read byte
			void readArray(long addr, byte data[], int length);        // read array
        
            byte readStatus();                                        // read status register
            void writeStatus(byte data);                              // write status register

            void pageErase(long addr);                                // erase page
            void sectorErase(long addr);                              // erase sector
            void chipErase();                                         // erase chip
        
            void deepPowerDown();                                     // Deep power-down mode
            byte releasePowerDown();                                  // release from Deep power-down and read electronic signature

		private:
            byte _cs;                                                 // chip select pin
            void enableWrite();                                       // enable write
			void sendAddress(long addr);                              // send 24-bit address
			bool WIP();                                               // write in progress ?
	};
	
#endif // MC25LC1024_h
