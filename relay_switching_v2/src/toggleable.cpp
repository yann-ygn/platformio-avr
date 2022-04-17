#include <Arduino.h>

#include "toggleable.hpp"

using namespace hal;

void Toggleable::setup() {
  pinMode(m_pin, OUTPUT);
  digitalWrite(m_pin, m_state);
}

void Toggleable::turnOn() {
  m_state = 1;
  digitalWrite(m_pin, m_state);
}

void Toggleable::turnOff() {
  m_state = 0;
  digitalWrite(m_pin, m_state);
}

void Toggleable::toggleState() {
  m_state = !m_state;
  digitalWrite(m_pin, m_state);
}

void Toggleable::setState(uint8_t state) {
  m_state = state;
  digitalWrite(m_pin, m_state);
}
