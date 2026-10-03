#pragma once

#include <stdint.h>

// Debounced, active-low momentary button using INPUT_PULLUP wiring.
class Button {
public:
    explicit Button(uint8_t pin, uint16_t debounceMs = 30);

    void begin();

    // Call frequently from loop(). Returns true once for each press.
    bool update();

private:
    uint8_t pin_;
    uint16_t debounceMs_;
    uint8_t rawState_;
    uint8_t stableState_;
    unsigned long lastRawChangeAt_;
};
