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

        if ((newByte & 0x80) 
        && ((newByte & 0xF) == m_midiChannel)) // Check that this is a status message on our channel
        {
            m_statusByte = newByte;
            m_commandCode = newByte & 0x80;
            m_channelInformation = newByte & 0xF;

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
        else
        {
            if ((m_commandCode == MIDI_PC) 
            && (m_dataByte1 == 0x0) 
            && ((newByte & 0x80) == 0)) // Data byte for the PC message
            {
                m_dataByte1 = newByte;

                #ifdef DEBUG
                    Serial.print("PC data received : ");
                    Serial.println(m_dataByte1);
                #endif

                return true; // Complete message
            }

            if ((m_commandCode == MIDI_CC) 
            && (m_dataByte1 == 0x0) 
            && (m_dataByte2 == 0x0) 
            && ((newByte & 0x80) == 0)) // First data byte for the CC message
            {
                m_dataByte1 = newByte;

                #ifdef DEBUG
                    Serial.print("CC data 1 received : ");
                    Serial.println(m_dataByte1);
                #endif

                return false; // Incomplete message
            }

            if ((m_commandCode == MIDI_CC) 
            && (m_dataByte1 != 0x0) 
            && ((m_dataByte2 == 0x0)) 
            && ((newByte & 0x80) == 0)) // Second data byte of the CC message
            {
                m_dataByte2 = newByte;

                #ifdef DEBUG
                    Serial.print("CC data 2 received : ");
                    Serial.println(m_dataByte2);
                #endif

                return true; // Completed message
            }

            else // Weird case or wrong channel
            {
                #ifdef DEBUG
                    Serial.print("WTF : ");
                    Serial.println(newByte);
                #endif

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