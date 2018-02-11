#include "FastLED.h"

#define NUM_LEDS 1
#define DATA_PIN 0
#define SERIAL_LOGGING

CRGB leds[NUM_LEDS];
static uint8_t heatIndex = 0;
const byte buttonPin = 13;
uint8_t headIndexStart = 90;

void setup()
{
#ifdef SERIAL_LOGGING
  Serial.begin(9600);
#endif
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
  static const uint32_t interval = (sunriseLength * 1000) / headIndexStart;

  EVERY_N_MILLISECONDS(interval)
  {
    if (heatIndex > 0)
    {
      heatIndex--;
#ifdef SERIAL_LOGGING
      Serial.println(heatIndex);
#endif
    }
  }
}
