#define FASTLED_INTERNAL
#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include "Patterns.h"
#include "Rotary.h"
#include "Potentiometer.h"

#define LED_PIN 1
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// Configure LEDs
CRGB leds[TOTAL_NUM_LEDS];               // Used only for display
CRGB pixels[TOTAL_NUM_LEDS_VISIBLE];     // Used for calculations
CRGB menuPixels[TOTAL_NUM_LEDS_VISIBLE]; // Used for menu display

// Potentiometers
Potentiometer pot1;
Potentiometer pot2;

// Rotary encoders
Rotary rot1;
Rotary rot2;

void setup()
{
  // Initialize serial
  Serial.begin(115200);

  // Initialize LEDs
  FastLED.addLeds<WS2812SERIAL, LED_PIN, GRB>(leds, TOTAL_NUM_LEDS);

  // Potentiometer connections
  pot1.init(analogInputToDigitalPin(6));
  pot2.init(analogInputToDigitalPin(7));

  // Rotary encoder connections
  rot1.init(analogInputToDigitalPin(3), analogInputToDigitalPin(4), analogInputToDigitalPin(5));
  rot2.init(analogInputToDigitalPin(0), analogInputToDigitalPin(1), analogInputToDigitalPin(2));

  attachInterrupt(
      digitalPinToInterrupt(analogInputToDigitalPin(4)), []()
      { rot1.update(); },
      CHANGE);
  attachInterrupt(
      digitalPinToInterrupt(analogInputToDigitalPin(5)), []()
      { rot1.update(); },
      CHANGE);
  attachInterrupt(
      digitalPinToInterrupt(analogInputToDigitalPin(1)), []()
      { rot2.update(); },
      CHANGE);
  attachInterrupt(
      digitalPinToInterrupt(analogInputToDigitalPin(2)), []()
      { rot2.update(); },
      CHANGE);

  FastLED.setDither(0);
  FastLED.show();
}

int lightMode = 0;
int rot1LastPos = 0;
int rot2LastPos = 0;
unsigned long lastEncoderChange = 0;
const unsigned long menuTimeout = 2000;
const unsigned long fadeTime = 1000;
const int numModes = 6;

void loop()
{
  // Check for potentiometer updates
  pot1.update();
  pot2.update();

  switch((rot1.value()%numModes+numModes)%numModes)
  // switch(4/)
  {
  case 0:
    Pride(pixels);
    break;
  case 1:
    SimpleNoise(pixels, rot2.value() * 4, pot2.value());
    break;
  case 2:
    RadialPulse(pixels, rot2.value() * 4, pot2.value());
    break;
  case 3:
    Pacifica(pixels);
    break;
  case 4:
    Twinkle(pixels, rot2.value() * 4, pot2.value());
    break;
  case 5:
    break;
  case 6:
    break;
    // rainbow();
    // pulse();
    // colorWipe();
    // rain();
    // theaterChase(); // no idea what this is
    // lixagonChase();
  default:
    for (int i = 0; i < TOTAL_NUM_LEDS_VISIBLE; i++)
    {
      pixels[i] = CRGB::Black;
    }
    break;
  }

  // Menu
  if (rot1.value() != rot1LastPos)
  {
    rot1LastPos = rot1.value();
    lastEncoderChange = millis();
  }
  if (menuTimeout > millis() - lastEncoderChange)
  {
    RayBeam(menuPixels, rot1.value() * 32768 / numModes);

    if (menuTimeout - fadeTime < millis() - lastEncoderChange){
      // if(true){
      for (int i = 0; i < TOTAL_NUM_LEDS_VISIBLE; i++)
      {
        menuPixels[i] %= (int)(255 - 255.0 * (millis() - lastEncoderChange - menuTimeout + fadeTime) / fadeTime);
        if(i == 1){
          Serial.println((int)(255 - 255.0 * (millis() - lastEncoderChange - menuTimeout + fadeTime) / fadeTime));
        }
      }
    }
  }

  // Update LEDs
  FastLED.setBrightness(pot1.value());

  // FastLED.setBrightness(255);
  if (lastEncoderChange + menuTimeout > millis())
  {
    for (int i = 0; i < TOTAL_NUM_LEDS_VISIBLE; i++)
    {
      leds[projectionMask(i)] = pixels[i] + menuPixels[i];
    }
  }
  else
  {
    for (int i = 0; i < TOTAL_NUM_LEDS_VISIBLE; i++)
    {
      leds[projectionMask(i)] = pixels[i];
    }
  }

  // Apply updates

  FastLED.show();
}