#include "FastLED.h"

#define NUM_LEDS 1
#define DATA_PIN 0
#define BUTTON_PIN 3

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON_PIN) != LOW)
  {
    leds[0].red = 0;
    leds[0].green = 0;
    leds[0].blue = 255;
  }
  else
  {
    leds[0].red = 255;
    leds[0].green = 0;
    leds[0].blue = 0;
  }
  FastLED.show();
}
