#include <Arduino.h>

// Colors
#define RESET   "\e[1;0m"
#define WHITE   "\e[1;037m"
#define BLACK   "\e[1;030m"
#define RED     "\e[0;031m"
#define GREEN   "\e[1;032m"
#define YELLOW  "\e[1;033m"
#define BLUE    "\e[1;034m"
#define MAGENTA "\e[1;035m"
#define CYAN    "\e[1;036m"

// Decorations
#define BOLD      "\e[1;1m"
#define UNDERLINE "\e[1;4m"

/**
 * @brief Reset the default character
 *
 */
void initLog();

/**
 * @brief
 *
 * @param periph 1: encoder, 2: LED, 3: switch, 4: potentiometer
 * @param periphPinNumber
 * @param message
 * @param messageColor
 */
void test();