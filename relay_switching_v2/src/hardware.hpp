#include <Arduino.h>

#include "switch.hpp"
#include "toggleable.hpp"

#ifndef HARDWARE_H
#define HARDWARE_H

namespace hw {
  // Pins declarartions
  constexpr uint8_t startupStatePin = 2;
  constexpr uint8_t footswitchPin = 1;
  constexpr uint8_t stateLedPin = 3;
  constexpr uint8_t relayPin = 4;
  constexpr uint8_t optocouplerPin = 5;

  class Hardware {
    public:
      void setuphardware();
      void pollHardware();
      void processHardware();

    private:
      bool m_footswitchPushed = false;

      bool readStartupState();
      void toggleBypass();
      void resetTriggers();
  };
}

#endif
