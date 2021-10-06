#include <Arduino.h>

// Colors
#define RESET   "\e[0;0m"
#define WHITE   "\e[0;037m"
#define BLACK   "\e[0;030m"
#define RED     "\e[0;031m"
#define GREEN   "\e[0;032m"
#define YELLOW  "\e[0;033m"
#define BLUE    "\e[0;034m"
#define MAGENTA "\e[0;035m"
#define CYAN    "\e[0;036m"

// Colors
#define WHITEBOLD   "\e[1;037m"
#define BLACKBOLD   "\e[1;030m"
#define REDBOLD     "\e[1;031m"
#define GREENBOLD   "\e[1;032m"
#define YELLOWBOLD  "\e[1;033m"
#define BLUEBOLD    "\e[1;034m"
#define MAGENTABOLD "\e[1;035m"
#define CYANBOLD    "\e[1;036m"

/**
 * @brief Reset to the default format
 */
void initLog();

/**
 * @brief Dummy test method
 */
void test();

/**
 * @brief
 *
 * @param periph pin #
 * @param action 1 : pushed | 2 : switched | 3: released
 */
void logSwitchAction(uint8_t periph, uint8_t action);