/*
  SSR.cpp - Simple Arduino Library to control an SSR
  Copyright (c) 2020 Hermann Gebhard. All right reserved.

*/

#include <Arduino.h>
#include "SSR.h"

void SSR::setDefaults(){
  _setting = 0;
  _counter = 0;
  _mode = MODE_ON_OFF;
  _inverted = false;
  _frequency = 10;
  _periodTime = 100;
}

SSR::SSR(void) {
  SSR::setDefaults();
}

SSR::SSR(uint8_t pin) {
  SSR::setDefaults();
  pinMode(pin, OUTPUT);
  _pin = pin;
}

SSR::run(void) {
  

  if (_mode == MODE_ON_OFF) {
    digitalWrite(_pin, _inverted ^ (_setting > 0));
  }
  else if (_mode == MODE_PULSE_PACKET){
    if ((millis() - _lastRun) >= _periodTime) {
      _lastRun +=  _periodTime;
      _counter += _setting;
      if (_counter >= 100) _counter -= 100;
      digitalWrite(_pin, _inverted ^ (_counter < _setting));
    }
  }
  else {
    digitalWrite(_pin, _inverted); // switch off
  }
}


void SSR::setup (uint8_t pin) {
  SSR::setDefaults();
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void SSR::setup (uint8_t pin, SSR_MODE_t mode) {
  SSR::setDefaults();
  _pin = pin;
  pinMode(_pin, OUTPUT);

  _mode = mode;
}

void SSR::setup (uint8_t pin, SSR_MODE_t mode, bool inverted) {
  SSR::setDefaults();
  _pin = pin;
  pinMode(_pin, OUTPUT);

  _mode = mode;
  _inverted = inverted;
}

void SSR::setup (uint8_t pin, SSR_MODE_t mode, bool inverted, uint8_t mainsFrequency) {
  _pin = pin;
  pinMode(_pin, OUTPUT);

  _mode = mode;
  _inverted = inverted;
  _frequency = mainsFrequency;
  _periodTime = 1000 / _frequency;
}

void SSR::setPower(uint8_t value) {
  _setting = (value <= 100 ? value : 100);
}
