#include <Arduino.h>

#ifndef TOGGEABLE_H
#define TOGGEABLE_H

namespace hal {
  class Toggleable {
    protected:
      uint8_t m_pin;
      uint8_t m_state = 0;

    public:
      Toggleable(uint8_t pin) : m_pin(pin) { }

      void setup();
      void turnOn();
      void turnOff();
      void toggleState();
      void setState(uint8_t state);
  };
}

#endif
