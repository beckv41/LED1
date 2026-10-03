#include <Arduino.h>
#include <FastLED.h>

#include "Button.h"
#include "LEDSection.h"

constexpr uint8_t LED_PIN = 18;
constexpr uint16_t NUM_LEDS = 52;
constexpr uint8_t BRIGHTNESS = 100;

constexpr uint8_t POWER_BUTTON_PIN = 25;
constexpr uint8_t COLOR_BUTTON_PIN = 26;
constexpr uint16_t BUTTON_DEBOUNCE_MS = 30;

CRGB leds[NUM_LEDS];
LEDSection ledSection(leds, NUM_LEDS, 0, NUM_LEDS);

Button powerButton(POWER_BUTTON_PIN, BUTTON_DEBOUNCE_MS);
Button colorButton(COLOR_BUTTON_PIN, BUTTON_DEBOUNCE_MS);

const CRGB colors[] = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    CRGB(0, 255, 255),  // Cyan
    CRGB(255, 0, 255),  // Magenta
    CRGB(255, 255, 0)   // Yellow
};

constexpr uint8_t COLOR_COUNT = sizeof(colors) / sizeof(colors[0]);

bool lightsOn = false;
uint8_t currentColorIndex = 0;

void renderLights() {
    if (lightsOn) {
        ledSection.fill(colors[currentColorIndex]);
    } else {
        ledSection.clear();
    }

    FastLED.show();
}

void setup() {
    powerButton.begin();
    colorButton.begin();

    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    renderLights();  // Start powered off.
}

void loop() {
    if (powerButton.update()) {
        lightsOn = !lightsOn;
        renderLights();
    }

    if (colorButton.update()) {
        currentColorIndex = (currentColorIndex + 1) % COLOR_COUNT;

        // The selection can change while off; it appears next time power turns on.
        if (lightsOn) {
            renderLights();
        }
    }
}
