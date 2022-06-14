#include <Arduino.h>

#ifndef SWITCH_H
#define SWITCH_H

namespace hal {
  class TemporarySwitch {
    public:
      TemporarySwitch(uint8_t pin, uint16_t lpperiod = 1000) :
        m_pin(pin),
        m_longPressPeriod(lpperiod) {};

      void setup();

      void poll();

      bool isSwitched();

      bool isOn();

      bool isPushed();

      bool isReleased();

      bool isLongPress();

    private:
      uint8_t m_pin;

      uint8_t m_state = 0;
      uint8_t m_lastState = 0;
      uint8_t m_rawState = 0;
      uint8_t m_deglitchedState = 0;
      uint8_t m_debouncedState = 1;

      uint32_t m_now = 0;
      uint32_t m_deglitchTime = 0;
      uint32_t m_lastSwitchedTime = 0;
      uint32_t m_lastPushedTime = 0;
      const uint8_t m_deglitchPeriod = 30;
      const uint8_t m_debouncePeriod = 50;
      uint16_t m_longPressPeriod;

      uint8_t m_switched = 0;
      uint8_t m_longPress = 0;
      uint8_t m_longPressActive = 0;
  };
}

#endif
