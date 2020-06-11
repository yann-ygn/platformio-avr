#include <Arduino.h>

#ifndef BYPASS_H
#define BYPASS_H

/**
 * @brief Drives a relay/optocoupler pair to actually bypass or not the effect and act as a fake "on/off" switch.
 */
class Bypass
{
    private:
        uint8_t m_relayPin; // Relay pin #
        uint8_t m_okPin; // Optical relay pin #
        uint8_t m_bypassState = 0;

    public:
        /**
         * @brief Construct a new Bypass object
         * 
         * @param rpin Relay pin #
         * @param okpin Optical relay pin #
         */
        Bypass(uint8_t rpin, uint8_t okpin) : m_relayPin(rpin), m_okPin(okpin) { };

        /**
         * @brief Setup the µC's pins
         */
        void bypassSetup();

        /**
         * @brief Switch the bypass state
         */
        void bypassSwitch();

        /**
         * @brief Get the Bypass State object
         * 
         * @return uint8_t 
         */
        uint8_t getBypassState();

        /**
         * @brief Set the Bypass State object
         * 
         * @param state 
         */
        void setBypassState(uint8_t state);
};

#endif