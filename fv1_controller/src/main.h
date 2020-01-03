#include <Arduino.h>

/**
 * @brief Selector interrupt function
 */
void selectorInterrupt();

/**
 * @brief Bypass interrupt function
 */
void bypassInterrupt();

/**
 * @brief Midi handler function
 * 
 * @param message 
 * @param byte1 
 * @param byte2 
 */
void midiHandler(uint8_t message, uint8_t byte1, uint8_t byte2);