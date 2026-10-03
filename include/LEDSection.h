#pragma once

#include <FastLED.h>
#include <stdint.h>

// A logical range of LEDs backed by a shared FastLED pixel buffer.
// Pixel indices passed to setPixel() are relative to this section.
class LEDSection {
public:
    LEDSection(CRGB* strip, uint16_t stripLength,
               uint16_t firstPixel, uint16_t pixelCount);

    uint16_t size() const;

    void fill(const CRGB& color);
    void clear();
    bool setPixel(uint16_t index, const CRGB& color);

private:
    CRGB* strip_;
    uint16_t firstPixel_;
    uint16_t pixelCount_;
};
