#include <Arduino.h>

#include "switch.hpp"
#include "toggleable.hpp"

#ifndef HARDWARE_H
#define HARDWARE_H

namespace hw {
  // Pins declarartions
  constexpr uint8_t startupStatePin = 4;
  constexpr uint8_t footswitchPin = 3;
  constexpr uint8_t stateLedPin = 0;
  constexpr uint8_t relayPin = 2;
  constexpr uint8_t optocouplerPin = 1;

  class Hardware {
    public:
      void setuphardware();
      void pollHardware();
      void processHardware();

    private:
      bool m_triggered = false;
      bool m_footswitchPushed = false;

      bool readStartupState();
      void toggleBypass();
      void resetTriggers();
  };
}

#endif
