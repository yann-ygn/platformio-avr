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
         * @brief Selects the memory address to write or read
         * 
         * @param address 
         */
        void sendAddress(uint32_t address);

        /**
         * @brief Returns the status register
         * 
         * @return uint8_t 
         */
        uint8_t readStatusRegister();

        /**
         * @brief Check the status of the WIP bit
         * 
         * @return true if a read/write is still in progress
         * @return false 
         */
        bool isWip();

    public:
        /**
         * @brief Construct a new Eeprom object
         * 
         * @param pin CS pin #
         */
        Eeprom(uint8_t pin) : m_csPin(pin) { }

        /**
         * @brief Setups the µC's pins and start the SPI bus
         */
        void eepromSetup();

        /**
         * @brief Read a 8bit value from the select memory address
         * 
         * @param address 
         * @return uint8_t 
         */
        uint8_t readInt8(uint32_t address);

        /**
         * @brief Writes a 8 bit value to the selected memory address
         * 
         * @param address 
         * @param data 
         */
        void writeInt8(uint32_t address, uint8_t data);

        /**
         * @brief Read a 16bit value from the select memory address
         * 
         * @param address 
         * @return uint16_t 
         */
        uint16_t readInt16(uint32_t address);

        /**
         * @brief Writes a 16 bit value to the selected memory address
         * 
         * @param address 
         * @param data 
         */
        void writeInt16(uint32_t address, uint16_t data);

        #ifdef DEBUG
            void testInt8();
            void testInt16();
        #endif
};

#endif