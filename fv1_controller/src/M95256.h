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
 * 
 */
class M95256
{
    private:
        uint8_t m_csPin; // SS pin #, to be set

        /**
         * @brief 
         */
        void select();

        /**
         * @brief 
         */
        void deselect();

        /**
         * @brief 
         */
        void enableWrite();
        void sendAddress(long addr);
        bool WIP();
        byte readStatus();

    public:
        M95256(byte pin) : m_csPin(pin)
        {

        }
        void setup();
        void writeByte(long addr, byte data);
        void writeArray(long addr, byte data[], int length);
        byte readByte(long addr);
        void readArray(long addr, byte data[], int length);
};
	
#endif
