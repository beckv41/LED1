#include <Arduino.h>
#include <FastLED.h>

#include "LEDSection.h"

constexpr uint8_t LED_PIN = 18;
constexpr uint16_t NUM_LEDS = 52;
constexpr uint8_t BRIGHTNESS = 100;

CRGB leds[NUM_LEDS];

// These sections cover the strip: pixels 0-16, 17-34, and 35-51.
LEDSection leftSection(leds, NUM_LEDS, 0, 17);
LEDSection centerSection(leds, NUM_LEDS, 17, 18);
LEDSection rightSection(leds, NUM_LEDS, 35, 17);

void setup() {
    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);

    // Start with all pixels off.
    FastLED.clear();
    FastLED.show();
}

void loop() {
    // Each section uses its own zero-based pixel range.
    leftSection.fill(CRGB::Red);
    centerSection.fill(CRGB::Green);
    rightSection.fill(CRGB::Blue);

    // LEDSection changes the shared pixel buffer.
    // FastLED.show() sends all section changes to the strip at once.
    FastLED.show();
    delay(1000);

    leftSection.clear();
    centerSection.clear();
    rightSection.clear();

    FastLED.show();
    delay(500);
}
