#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 11
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
static uint8_t heatIndex = 0;
const byte buttonPin = 13;
uint8_t headIndexStart = 90;

void setup()
{
  Serial.begin(9600);
  Serial.write("Ben Fade");
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(buttonPin, INPUT_PULLUP);
    heatIndex = headIndexStart;
}

void loop()
{
  if (digitalRead(buttonPin) != LOW && heatIndex == 0)
  {
    heatIndex = headIndexStart;
  }

  sunrise();
  FastLED.show();
}

void sunrise()
{
  CRGB color = ColorFromPalette(HeatColors_p, heatIndex);
  fill_solid(leds, NUM_LEDS, color);
  
  static const uint32_t sunriseLength = 20;  // seconds
  static const uint32_t interval = (sunriseLength * 1000) / headIndexStart; // s
  // 256 gradient steps

  EVERY_N_MILLISECONDS(interval)
  {
    if (heatIndex > 0)
    {
      heatIndex--;
      Serial.println(heatIndex);
    }
  }
}
