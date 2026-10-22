#include <Arduino.h>
#include <FastLED.h>

#include "Button.h"

constexpr uint8_t LED_PIN = 18;
constexpr uint16_t SCAN_CAPACITY = 120;
constexpr uint8_t BRIGHTNESS = 64;

constexpr uint8_t UP_BUTTON_PIN = 25;
constexpr uint8_t DOWN_BUTTON_PIN = 26;
constexpr uint16_t DEBOUNCE_MS = 30;
constexpr unsigned long BLINK_INTERVAL_MS = 500;

CRGB leds[SCAN_CAPACITY];

Button upButton(UP_BUTTON_PIN, DEBOUNCE_MS);
Button downButton(DOWN_BUTTON_PIN, DEBOUNCE_MS);

uint16_t cellIndex = 0;  // Zero-based index of the selected cell
bool blinkOn = true;
unsigned long lastBlinkAt = 0;

void showSelectedCell() {
    fill_solid(leds, SCAN_CAPACITY, CRGB::Black);

    if (blinkOn) {
        leds[cellIndex] = CRGB::White;
    }

    FastLED.show();
}

void reportCell() {
    Serial.printf("Selected cell: %u (index %u)\n",
                  cellIndex + 1, cellIndex);
}

void setup() {
    Serial.begin(115200);

    upButton.begin();
    downButton.begin();

    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, SCAN_CAPACITY);
    FastLED.setBrightness(BRIGHTNESS);

    lastBlinkAt = millis();
    reportCell();
    showSelectedCell();
}

void loop() {
    const unsigned long now = millis();
    bool selectionChanged = false;

    if (upButton.update() && cellIndex < SCAN_CAPACITY - 1) {
        ++cellIndex;
        selectionChanged = true;
    }

    if (downButton.update() && cellIndex > 0) {
        --cellIndex;
        selectionChanged = true;
    }

    if (selectionChanged) {
        blinkOn = true;
        lastBlinkAt = now;
        reportCell();
        showSelectedCell();
    }

    if (now - lastBlinkAt >= BLINK_INTERVAL_MS) {
        lastBlinkAt = now;
        blinkOn = !blinkOn;
        showSelectedCell();
    }
}