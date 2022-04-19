#include <Arduino.h>

#include "hardware.hpp"

hw::Hardware hardware;

void setup() {
  hardware.setuphardware();
}

void loop() {
  hardware.pollHardware();
  hardware.processHardware();
}
