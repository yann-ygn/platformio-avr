#include <Arduino.h>

#ifndef MIDI_H
#define MIDI_H

#define MIDI_PC 0x40 // 01000000
#define MIDI_CC 0x30 // 00110000

#define MIDI_POT0 0x3 // POT0 Pot
#define MIDI_POT1 0x9 // POT1 Pot
#define MIDI_POT2 0xE // POT2 Pot
#define MIDI_POT3 0xF // MIX Pot
#define MIDI_BYPASS 0x10 // BYPASS Switch
#define MIDI_TAP 0x11 // TAP Switch
#define MIDI_TAPLP 0x12 // TAP Switch long press
#define MIDI_DIV 0x13 // DIV

class Midi
{
    private:
        uint8_t m_midiChannel = 0;
        uint8_t m_statusByte = 0;
        uint8_t m_commandCode = 0;
        uint8_t m_channelInformation = 0;
        uint8_t m_dataByte1 = 0;
        uint8_t m_dataByte2 = 0;

    public:
        /**
         * @brief Sets up the serial port.
         */
        void midiSetup();

        /**
         * @brief Process the incoming data bytes to form complete MIDI PC and CC messages.
         * 
         * @return true 
         * @return false 
         */
        bool completeMidiMessage();

        /**
         * @brief Resets the MIDI message data members.
         */
        void resetMidiMessage();

        /**
         * @brief Get the Midi Channel object
         * 
         * @return uint8_t 
         */
        uint8_t getMidiChannel();

        /**
         * @brief Set the Midi Channel object
         * 
         * @param channel 
         */
        void setMidiChannel(uint8_t channel);

        /**
         * @brief Get the Command Code object
         * 
         * @return uint8_t 
         */
        uint8_t getCommandCode();

        /**
         * @brief Get the Data Byte1 object
         * 
         * @return uint8_t 
         */
        uint8_t getDataByte1();

        /**
         * @brief Get the Data Byte2 object
         * 
         * @return uint8_t 
         */
        uint8_t getDataByte2();
};

#endif
