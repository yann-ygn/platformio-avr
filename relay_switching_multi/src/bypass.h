#include <Arduino.h>

#ifndef BYPASS_H
#define BYPASS_H

/**
 * @brief A switch is connected to the µC along with a relay, an opticalrelay and an LED.
 * It has to be setup once, can read the state of the footswitch and swith the state 
 * of the relay/opticalrelay/LED combination. A jumper is also connected and used to set the startup state.
 */
class Bypass
{
    private:
        uint8_t m_relayPin;
        uint8_t m_ledPin;
        uint8_t m_led2Pin;
        uint8_t m_okPin;
        uint8_t m_switchPin;
        uint8_t m_activeLed = 0;
        unsigned long m_lastPressTime = 0;
        uint8_t m_switchState = 0;
        uint8_t m_lastSwitchState = 0;
        uint8_t m_relayState = 0;
        const unsigned int c_debounceTime = 300; // Minimum delay between 2 footswitch press, in ms.

    public:
        Bypass (uint8_t rpin, uint8_t lpin, uint8_t l2pin, uint8_t opin, uint8_t spin) : 
                m_relayPin(rpin), m_ledPin(lpin), m_led2Pin(l2pin), m_okPin(opin), m_switchPin(spin)
        {

        }

        /**
         * @brief Setup the µC's pins, read the startup state and set the relay/LED accordingly.
         */
        void bypassSetup();

        /**
         * @brief Read the footswitch state.
         * 
         * @return true if LOW and if the debounce delay has passed and if its state changed since the last cycle.
         * @return false 
         */
        bool bypassPressed();

        /**
         * @brief Switch the relay/LED state.
         */
        void switchRelay();

        /**
         * @brief Switch the active LED
         */
        void switchActiveLed();

        /**
         * @brief Turn on/off the active LED
         */
        void lightActiveLed();

        unsigned long m_now = 0;
};

#endif