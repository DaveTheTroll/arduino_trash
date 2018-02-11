#include "FastLED.h"

#define DATA_PIN 0

const byte ledPin = 0;  // Pin on which LED data is send
const byte buttonPin = 3; // Pin button is connected to
CRGB led; // current LED color, refenced by FastLED library
uint8_t glowIndex = 0;  // current index into palette of glow colour
const uint8_t glowStart = 90; // Starting index into palette that glow starts
const uint32_t glowDuration = 20;  // Number of seconds from start to finish of glow
const uint32_t interval = (glowDuration * 1000) / glowStart;  // Time between glow index changes to achieve glow duration

void setup()
{
  // Configure LED and button
  FastLED.addLeds<NEOPIXEL, ledPin>(&led, 1);
  pinMode(buttonPin, INPUT_PULLUP);
  // Set LED to off.
  setLED();
}

void loop()
{
  // If button pressed and system glow ready start glow.
  if (buttonPressed() && glowFinished)
  {
    startGlow();
  }

  // Update glow colour based on time
  glow();
  FastLED.show();
}

// True if button is currently pressed
bool buttonPressed() {return digitalRead(buttonPin) != LOW;}
// True if LED off and glow complete
bool glowFinished() {return glowIndex == 0;}
// start new glow sequence
void startGlow()
{
  glowIndex = glowStart;
  setLED();
}
// Set LED to current index colour
void setLED()
{
    CRGB color = ColorFromPalette(HeatColors_p, glowIndex);
    led = color;
}
 
// Update glow colour based on time
void glow()
{
  EVERY_N_MILLISECONDS(interval)
  {
    if (glowIndex > 0)
    {
      glowIndex--;
      setLED();
    }
  }
}
