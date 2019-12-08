#include <Arduino.h>

#ifndef M95256_H
#define M95256_H

#define READ  B00000011
#define WRITE B00000010
#define WREN  B00000110
#define WRDI  B00000100
#define RDSR  B00000101
#define WRSR  B00000001

/**
 * @brief Interface for the ST M95256 EEPROM
 */
class M95256
{
    private:
        uint8_t m_csPin; // SS pin #, to be set with the constructor

        /**
         * @brief Setup the SPI bus and select the chip
         */
        void select();

        /**
         * @brief Deselect the chip and close the SPI bus
         */
        void deselect();

        /**
         * @brief Selects  the chip, enable the write instruction and deselect
         */
        void enableWrite();

        /**
         * @brief Sets the address we're writing to
         * 
         * @param addr 
         */
        void sendAddress(long addr);

        /**
         * @brief Read the status register
         * 
         * @return byte 
         */
        byte readStatus();

        /**
         * @brief Read the WIP bit in the status register
         * 
         * @return true 
         * @return false 
         */
        bool WIP();

    public:
        /**
         * @brief Construct a new M95256 object
         * 
         * @param pin CS pin #
         */
        M95256(byte pin) : m_csPin(pin)
        {

        }

        /**
         * @brief Set the µC's pin and start the SPI bus
         */
        void setup();

        void writeByte(long addr, byte data);
        void writeArray(long addr, byte data[], int length);
        byte readByte(long addr);
        void readArray(long addr, byte data[], int length);
};
	
#endif
