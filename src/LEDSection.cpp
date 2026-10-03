#include "LEDSection.h"

LEDSection::LEDSection(CRGB* strip, uint16_t stripLength,
                       uint16_t firstPixel, uint16_t pixelCount)
    : strip_(strip),
      firstPixel_(firstPixel <= stripLength ? firstPixel : stripLength),
      pixelCount_(0)
{
    if (strip_ == nullptr) {
        return;
    }

    const uint16_t available = stripLength - firstPixel_;
    pixelCount_ = pixelCount < available ? pixelCount : available;
}

uint16_t LEDSection::size() const {
    return pixelCount_;
}

void LEDSection::fill(const CRGB& color) {
    for (uint16_t i = 0; i < pixelCount_; ++i) {
        strip_[firstPixel_ + i] = color;
    }
}

void LEDSection::clear() {
    fill(CRGB::Black);
}

bool LEDSection::setPixel(uint16_t index, const CRGB& color) {
    if (index >= pixelCount_) {
        return false;
    }

    strip_[firstPixel_ + index] = color;
    return true;
}
