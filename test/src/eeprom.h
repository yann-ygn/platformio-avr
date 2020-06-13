#include <Arduino.h>

#ifndef EEPROM_H
#define EEPROM_H

#define READ  B00000011
#define WRITE B00000010
#define WREN  B00000110
#define WRDI  B00000100
#define RDSR  B00000101
#define WRSR  B00000001

/**
 * @brief Interface for a serial eeprom (M95256), supports read/write of various data types
 */
class Eeprom
{
    private:
        uint8_t m_csPin; // CS pin #

        /**
         * @brief Setup the SPI bus and select the chip
         */
        void select();

        /**
         * @brief Deselect the chip and close the SPI bus
         */
        void deselect();

        /**
         * @brief Select the chip, send the WREN instruction and deselect
         */
        void enableWrite();

        /**
         * @brief Returns the status register
         * 
         * @return uint8_t 
         */
        uint8_t readStatusRegister();

        /**
         * @brief 
         * 
         * @param address 
         */
        void sendAddres(uint16_t address);

    public:
};

#endif