/*#include <Arduino.h>
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

    Serial.begin(115200);

    powerButton.begin();
    colorButton.begin();

    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    renderLights();  // Start powered off.
}

void loop() {

    
static unsigned long lastReport = 0;

if (powerButton.update()) {
    lightsOn = !lightsOn;
    Serial.printf("Power pressed; lightsOn=%d\n", lightsOn);
    renderLights();
}

if (colorButton.update()) {
    currentColorIndex = (currentColorIndex + 1) % COLOR_COUNT;
    Serial.printf("Color pressed; index=%u\n", currentColorIndex);
    if (lightsOn) renderLights();
}

if (millis() - lastReport >= 500) {
    lastReport = millis();
    Serial.printf("GPIO25=%d GPIO26=%d lightsOn=%d\n",
                  digitalRead(25), digitalRead(26), lightsOn);
}


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


#include <FastLED.h>

constexpr uint8_t LED_PIN = 18;
constexpr uint16_t NUM_LEDS = 10;
CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(64);

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[0] = CRGB::Red;
    FastLED.show();
}

void loop() {}

*/

#include <Arduino.h>
#include <FastLED.h>

constexpr uint8_t LED_PIN = 18;
constexpr uint16_t NUM_LEDS = 10;
constexpr uint8_t BRIGHTNESS = 64;

CRGB leds[NUM_LEDS];

CRGB colors[] = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue
};


void setup() {
    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
   for(int j = 0; j < 3; j++)
    {
        FastLED.clear();

        for(int i=0; i<NUM_LEDS;i++)
        {
            
            leds[i]=colors[j];
            FastLED.show();
            
        }
        delay(1000);
    } 
}

/* THIS CODE IS WORKING
#include <FastLED.h>



#define LED_PIN 18
#define NUM_LEDS 52

CRGB leds[NUM_LEDS];

CRGB colors[] = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue
};



void setup() {

    FastLED.addLeds<WS2811, LED_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(100);


}

void loop()
{

    for(int j = 0; j < 3; j++)
    {
        FastLED.clear();

        for(int i=0; i<NUM_LEDS;i++)
        {
            
            leds[i]=colors[j];
            FastLED.show();
            
        }
        delay(1000);
    }
}

//note new LED dims are 6mm wide, 15mm tall, light is upper 3.5mm
*/