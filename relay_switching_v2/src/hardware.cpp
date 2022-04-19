#include "hardware.hpp"

using namespace hw;

hal::TemporarySwitch footswitch(footswitchPin);
hal::Toggleable stateLed(stateLedPin);
hal::Toggleable relay(relayPin);
hal::Toggleable optocoupler(optocouplerPin);

void Hardware::setuphardware() {
  footswitch.setup();
  stateLed.setup();
  relay.setup();
  optocoupler.setup();

  if (readStartupState()) {
    toggleBypass();
  }
}

void Hardware::pollHardware() {
  footswitch.poll();

  if (footswitch.isPushed()) {
    m_footswitchPushed = true;
  }
}

void Hardware::processHardware() {
  if (m_footswitchPushed == true) {
    toggleBypass();
  }

  resetTriggers();
}

bool Hardware::readStartupState() {
  return digitalRead(startupStatePin);
}

void Hardware::toggleBypass() {
  optocoupler.toggleState();
  delay(10);
  relay.toggleState();
  stateLed.toggleState();
  delay(10);
  optocoupler.toggleState();
}

void Hardware::resetTriggers() {
  m_footswitchPushed = false;
}