#include <Arduino.h>
#include "switch.hpp"

using namespace hal;

void TemporarySwitch::setup() {
    pinMode(m_pin, INPUT_PULLUP);
}

void TemporarySwitch::poll() {
  m_state = digitalRead(m_pin);
  m_now = millis();

  if (m_state == m_lastState) {
    m_rawState = 1;
  }
  else {
    m_rawState = 0;
    m_deglitchTime = m_now;
  }

  if (m_rawState && ((m_now - m_deglitchTime) > m_deglitchPeriod)) {
    m_deglitchedState = m_state;
    m_deglitchTime = m_now;
  }

  m_lastState = m_state;

  m_switched = 0;

  if ((m_deglitchedState != m_debouncedState) && (m_now - m_lastSwitchedTime) > m_debouncePeriod) {
    m_debouncedState = m_deglitchedState;
    m_switched = 1;
  }

  m_switched = 0;

  if (isReleased()) {
    m_longPressActive = false;
  }

  if (!m_longPressActive) {
    m_longPress = !isSwitched() && isOn() &&((m_now - m_lastPushedTime) > m_longPressPeriod);
    m_longPressActive = m_longPress;
  }

  if (isSwitched()) {
    m_lastSwitchedTime = m_now;

    if (isPushed()) {
        m_lastPushedTime = m_now;
    }
  }
}

bool TemporarySwitch::isSwitched() {
  return m_switched;
}

bool TemporarySwitch::isOn() {
  return !m_debouncedState;
}

bool TemporarySwitch::isPushed() {
  return m_switched && !m_debouncedState;
}

bool TemporarySwitch::isReleased() {
  return m_switched && m_debouncedState;
}

bool TemporarySwitch::isLongPress() {
  return m_longPress;
}
