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
        void sendAddress(uint16_t address);
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
         * @brief Returns the status register
         *
         * @return uint8_t
         */
        uint8_t readStatusRegister();

        /**
         * @brief Reset the status register to its initial value b00000010
         */
        void writeStatusRegister();


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
        uint8_t readInt8(uint16_t address);

        void readInt8(uint16_t address, uint8_t* data);

        /**
         * @brief Writes a 8 bit value to the selected memory address
         *
         * @param address
         * @param data
         */
        void writeInt8(uint16_t address, uint8_t data);

        /**
         * @brief Read a 16bit value from the selected memory address
         *
         * @param address
         * @return uint16_t
         */
        uint16_t readInt16(uint16_t address);

        /**
         * @brief Writes a 16 bit value to the selected memory address
         *
         * @param address
         * @param data
         */
        void writeInt16(uint16_t address, uint16_t data);

        /**
         * @brief Read an array of 8 bits integer starting at the selected memory address
         *
         * @param address
         * @param data
         * @param length
         */
        void readArray(uint16_t address, uint8_t* data, uint8_t length);

        /**
         * @brief Write an array of 8 bits integer starting at the selected memory address
         *
         * @param address
         * @param data
         * @param length
         */
        void writeArray(uint16_t address, uint8_t* data, uint8_t length);

        #ifdef DEBUG
            void testInt8();
            void testInt16();
            void testArray();
            uint8_t test();
        #endif
};

#endif