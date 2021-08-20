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
        void BypassSwitch(uint8_t state);
};

#endif