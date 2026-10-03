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
