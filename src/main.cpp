#include <Arduino.h>
#include <FastLED.h>

#include "Button.h"
#include "LEDSection.h"

constexpr uint8_t LED_PIN = 18;
constexpr uint16_t NUM_LEDS = 52;
constexpr uint8_t BRIGHTNESS = 100;

constexpr uint8_t BUTTON_1_PIN = 25;
constexpr uint8_t BUTTON_2_PIN = 26;
constexpr uint16_t DEBOUNCE_MS = 30;

constexpr unsigned long PIXEL_INTERVAL_MS = 15;
constexpr unsigned long COLOR_HOLD_MS = 1000;

CRGB leds[NUM_LEDS];

LEDSection testSection(leds, NUM_LEDS, 0, NUM_LEDS);
Button button1(BUTTON_1_PIN, DEBOUNCE_MS);
Button button2(BUTTON_2_PIN, DEBOUNCE_MS);

const CRGB colors[] = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue
};

constexpr uint8_t COLOR_COUNT = sizeof(colors) / sizeof(colors[0]);

uint8_t activeColor = 0;
uint16_t nextPixel = 0;
unsigned long lastPixelAt = 0;
unsigned long colorFinishedAt = 0;
bool holdingColor = false;

void setup() {
    Serial.begin(115200);

    button1.begin();
    button2.begin();

    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    FastLED.show();
}

void loop() {
    // update() returns true once for each debounced press.
    if (button1.update()) {
        Serial.println("Button 1 pressed");
    }

    if (button2.update()) {
        Serial.println("Button 2 pressed");
    }

    const unsigned long now = millis();

    // Keep the sample color-fill running without blocking button polling.
    if (holdingColor) {
        if ((now - colorFinishedAt) >= COLOR_HOLD_MS) {
            activeColor = (activeColor + 1) % COLOR_COUNT;
            testSection.clear();
            FastLED.show();

            nextPixel = 0;
            holdingColor = false;
            lastPixelAt = now;
        }
        return;
    }

    if ((now - lastPixelAt) >= PIXEL_INTERVAL_MS) {
        lastPixelAt = now;

        if (nextPixel < testSection.size()) {
            testSection.setPixel(nextPixel, colors[activeColor]);
            ++nextPixel;
            FastLED.show();
        }

        if (nextPixel >= testSection.size()) {
            holdingColor = true;
            colorFinishedAt = now;
        }
    }
}
