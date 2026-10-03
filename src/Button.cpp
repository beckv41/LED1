#include <Arduino.h>

#include "Button.h"

Button::Button(uint8_t pin, uint16_t debounceMs)
    : pin_(pin),
      debounceMs_(debounceMs),
      rawState_(HIGH),
      stableState_(HIGH),
      lastRawChangeAt_(0)
{
}

void Button::begin() {
    pinMode(pin_, INPUT_PULLUP);
    rawState_ = digitalRead(pin_);
    stableState_ = rawState_;
    lastRawChangeAt_ = millis();
}

bool Button::update() {
    const unsigned long now = millis();
    const uint8_t reading = digitalRead(pin_);

    if (reading != rawState_) {
        rawState_ = reading;
        lastRawChangeAt_ = now;
    }

    if ((now - lastRawChangeAt_) >= debounceMs_ && reading != stableState_) {
        stableState_ = reading;
        return stableState_ == LOW;
    }

    return false;
}
