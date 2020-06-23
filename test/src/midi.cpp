#define DEBUG 1

#include <Arduino.h>

#include "midi.h"

void Midi::midiSetup()
{
    Serial.begin(31250);
}

bool Midi::completeMidiMessage()
{
    if (Serial.available()) // New data received
    {
        uint8_t newByte = Serial.read();

        if ((newByte & 0x80)  // & 10000000 is a status message
        && ((newByte & 0xF) == m_midiChannel)) // On the correct channel
        {
            m_statusByte = newByte;
            m_commandCode = newByte & 0x70; // & 01110000
            m_channelInformation = newByte & 0xF; // & 00001111

            #ifdef DEBUG
                Serial.print("Status byte received : ");
                Serial.println(m_statusByte);
                Serial.print("Command : ");
                Serial.println(m_commandCode);
                Serial.print("Channel : ");
                Serial.println(m_channelInformation);
            #endif

            return false; // Incomplete message
        }
        else // Not a status message
        {
            if ((m_commandCode == MIDI_PC)  // There's an incomplete PC message stored
            && (m_dataByte1 == 0x0)         // No data stored on byte1
            && ((newByte & 0x80) == 0))     // This is a data byte
            {
                m_dataByte1 = newByte;      // Save to byte1

                #ifdef DEBUG
                    Serial.print("PC data received : ");
                    Serial.println(m_dataByte1);
                #endif

                return true;                // Complete PC message
            }

            if ((m_commandCode == MIDI_CC)  // There's an incomplete CC message stored
            && (m_dataByte1 == 0x0)         // No data stored on byte1
            && (m_dataByte2 == 0x0)         // No data stored on byte2
            && ((newByte & 0x80) == 0))     // This is a data byte
            {
                m_dataByte1 = newByte;      // Save it to byte1

                #ifdef DEBUG
                    Serial.print("CC data 1 received : ");
                    Serial.println(m_dataByte1);
                #endif

                return false;               // Incomplete CC message
            }

            if ((m_commandCode == MIDI_CC)  // There's an incomplete CC message stored
            && (m_dataByte1 != 0x0)         // The incomplete message has valid byte1
            && (m_dataByte2 == 0x0)         // No data stored on byte2
            && ((newByte & 0x80) == 0))     // This is a data byte
            {
                m_dataByte2 = newByte;      // Save it to byte2

                #ifdef DEBUG
                    Serial.print("CC data 2 received : ");
                    Serial.println(m_dataByte2);
                #endif

                return true; // Complete CC message
            }

            else // Wrong channel or unsupported message, reset the pending data
            {
                #ifdef DEBUG
                    Serial.print("Unsupported message : ");
                    Serial.println(newByte);
                #endif

                resetMidiMessage();
                return false;
            }
        }        
    }
    else
    {
        return false;
    }
}

void Midi::resetMidiMessage()
{
    m_statusByte = 0;
    m_commandCode = 0;
    m_channelInformation = 0;
    m_dataByte1 = 0;
    m_dataByte2 = 0;
}

uint8_t Midi::getMidiChannel()
{
    return m_midiChannel;
}

void Midi::setMidiChannel(uint8_t channel)
{
    m_midiChannel = channel;
}

uint8_t Midi::getCommandCode()
{
    return m_commandCode;
}

uint8_t Midi::getDataByte1()
{
    return m_dataByte1;
}

uint8_t Midi::getDataByte2()
{
    return m_dataByte2;
}