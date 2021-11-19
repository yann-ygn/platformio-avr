#include <Arduino.h>

#ifndef LED_H
#define LED_H

/**
 * @brief Drives an LED, it can be turned on or off or have its state switched.
 */
class Led
{
    protected:
        uint8_t m_pin; // LED pin #
        uint8_t m_ledState = 0;

    public:
        /**
         * @brief Construct a new Led object
         *
         * @param pin LED pin #
         */
        Led(uint8_t pin) : m_pin(pin) { }

        /**
         * @brief Setup the µC's pins and set the LED to its startup state
         */
        void ledSetup();

        /**
         * @brief Turn the LED on
         */
        void ledTurnOn();

        /**
         * @brief Turn the LED off
         */
        void ledTurnOff();

        /**
         * @brief Set the LED to a desired state
         *
         * @param state
         */
        void ledSetState(uint8_t state);

        /**
         * @brief Switch the LED state off/on or on/off
         */
        void ledSwitchState();

        /**
         * @brief Get the Led State object
         *
         * @return uint8_t
         */
        uint8_t getLedState();

        /**
         * @brief Set the Led State object
         *
         * @param state
         */
        void setLedState(uint8_t state);
};

class PwmLed : public Led
{
    public:
    /**
     * @brief Construct a new Pwm Led object
     *
     * @param cspin
     */
    PwmLed(uint8_t pin) : Led(pin) { }

    /**
     * @brief Set the Pwm Led State object
     *
     * @param state
     */
    void setPwmLedState(uint8_t state);
};

#endif