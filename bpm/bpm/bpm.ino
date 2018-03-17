#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    150
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

int pulsePin = 11;                // Pulse Sensor purple wire connected to analog pin X

CRGB leds[NUM_LEDS];

CRGB normal(32, 255, 32);
CRGB high(255, 0, 0);
int highThreshold = 100;
int brighnessHi = 255;
int brightnessLo = 16;
int pulseLength = 50;
int pulseFactor = 4;

volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

void setup()
{
  Serial.begin(250000);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  
  BPM = 50;

// Uncomment to connect to pulse sensor.
// Also include interrupt.ino from flora-pulse-neopixels
//  delay(1000);                      // Wait a second
//  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
}

void loop()
{
  fill_solid(leds, NUM_LEDS, (BPM > highThreshold) ? high : normal);
  FastLED.setBrightness(brighnessHi);
  FastLED.delay(pulseLength);
  FastLED.show();
  FastLED.setBrightness(brightnessLo);
  FastLED.delay((60000*pulseFactor / BPM) - pulseLength);
  FastLED.show();

  if (Serial.available() > 0)
  {
    BPM = Serial.parseInt();
  }

}
