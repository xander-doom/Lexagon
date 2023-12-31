#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <map>
#include <utility>
#include <vector>
#include "Rotary.h"
#include "Potentiometer.h"
#include "Patterns.h"

#define LED_PIN 1
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define LEXAGON_NUM_LEDS 96
#define LIXAGON_NUM_LEDS 41
#define LIXAGON_NUM_LEDS_VISIBLE 24
#define TOTAL_NUM_LEDS LEXAGON_NUM_LEDS + LIXAGON_NUM_LEDS * 6
#define TOTAL_NUM_LEDS_VISIBLE LEXAGON_NUM_LEDS + LIXAGON_NUM_LEDS_VISIBLE * 6

// Configure LEDs
CRGB leds[TOTAL_NUM_LEDS];
CRGB pixels[TOTAL_NUM_LEDS_VISIBLE];

// Coordinate to Index and Index to Coordinate maps
// Coordinate system is custom
// Lexagon uses a cartesian coordinate system with 0,0 in the center middle
// Lixagon uses two circular coordinates, one for which Lixagon and one for which LED (out of 6 and 24 respectively)
// Index does NOT USE THE PROJECTION MAP. PROJECTION MAP IS APPLIED AT THE END
std::map<std::pair<int, int>, int> LexC2I; // Lexagon Coordinate to Index
std::map<int, std::pair<int, int>> LexI2C; // Lexagon Index to Coordinate
std::map<std::pair<int, int>, int> LexPol; // Lexagon Polar to Index
std::map<std::pair<int, int>, int> LixC2I; // Lixagon Coordinate to Index
std::map<int, std::pair<int, int>> LixI2C; // Lixagon Index to Coordinate
// Projection of normal LED index onto Lexagon and Lixagon (skip hidden LEDs in Lixagon)
// Used for mapping existing LED patterns to Lexagon
std::vector<int> projectionMask(TOTAL_NUM_LEDS_VISIBLE, 0);

// Potentiometers
Potentiometer pot1;
Potentiometer pot2;

// Rotary encoders
Rotary rot1;
Rotary rot2;

int lastms = 0;
int deltams = 0;

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
      digitalPinToInterrupt(4), []()
      { rot1.update(); },
      CHANGE);
  attachInterrupt(
      digitalPinToInterrupt(1), []()
      { rot2.update(); },
      CHANGE);

  /**
   ** Initialize the coordinate mapping for LEXAGON **
   */
  // Map the coordinates to the index of the LEDs
  int idx_lastrow = LEXAGON_NUM_LEDS;
  // Bottom to top
  for (int y = 0; y < 8; y++)
  {
    // Left to right
    int width[8] = {4, 5, 6, 7, 7, 6, 5, 4}; // Clearer to to hardcode this vs a loop
    for (int x = -width[y]; x <= width[y]; x++)
    {

      // Compensate for switchback wiring
      int idx;
      if (y % 2 == 0)
      {
        idx = idx_lastrow - x - width[y] - 1;
      }
      else
      {
        idx = idx_lastrow + x - width[y] - 1;
      }

      // Associate the coordinates with the index both ways
      LexC2I[std::make_pair(x, y)] = idx;
      LexI2C[idx] = std::make_pair(x, y);
      projectionMask[idx] = idx;

      // Todo add power on animation?
      leds[idx] = CRGB::White;
      FastLED.show();
    }

    // Update row index
    idx_lastrow -= width[y] * 2 + 1;
  }

  /**
   ** Initialize the coordinate mapping for LIXAGON **
   */

  // Clockwise around the hexes, starting at the bottom
  int idx = LEXAGON_NUM_LEDS;
  int ledidx = LEXAGON_NUM_LEDS; // led mapping for projection mask
  for (int i = 0; i < 6; i++)
  {
    int r = 0;
    // Counterclockwise around sides, starting where the wire comes in (first side twice)
    for (int j = 0; j < 7; j++)
    {
      // Along the LEDs on the side
      for (int k = 0; k < 7; k++)
      {
        if (j == 0 && k == 0) // Start in the middle of the first side
          k = 4;

        if (k % 2 == 0)
        {
          // Initalization code goes here
          // idx = global index of LED
          // i = lixagon
          // j = side of lixagon
          // k = LED on that side
          // r = index of LED in that lixagon
          LixC2I[std::make_pair(i, r)] = idx;
          LixI2C[idx] = std::make_pair(i, r);

          projectionMask[i * 24 + r + LEXAGON_NUM_LEDS] = ledidx;
          r++;

          idx++; // Pixel mapping. move outside of the if statment for led mapping.

          // Todo add power on animation?
          leds[ledidx] = CRGB::White;
          FastLED.show();
        }
        ledidx++; // led mapping for projection mask

        if (j == 6 && k == 2)
          break;
      }
    }
  }
}

int lightMode = 0;
int rot1LastPos = 0;
int rot2LastPos = 0;
unsigned long lastEncoderChange = 0;
const unsigned long menuTimeout = 5000;
const unsigned long fadeTime = 300;

void loop()
{

  // Check for potentiometer updates
  pot1.update();
  pot2.update();
  // Encoder updates are handled by interrupts (in setup)

  // Update time for patterns
  // Also allows for on-the-fly speed updates
  deltams = millis() - lastms;
  lastms = millis();

  // Todo remove this (probably making things mega slow)
  Serial.println(deltams);

  if (rot1.value() != rot1LastPos)
  {
    rot1LastPos = rot1.value();
    lastEncoderChange = millis();
  }

  // if(lastEncoderChange + menuTimeout > millis())
  if (false)
  {
    for (int i = 0; i < TOTAL_NUM_LEDS; i++)
    {
      pixels[i] = 0;
    }

    pixels[rot1.value()] = 0xffffff;
    Serial.println(rot1.value());
    Serial.println(rot1.value() % 100);
  }
  else
  { 
    //Macro expands to non-blocking timed loop //todo assess if this is a bad idea lol
    //EVERY_N_MILLISECONDS_I(refreshRate, 20)
    if(true)
    {
      // Update refresh rate based on pot1
      //refreshRate.setPeriod(pot1.value() / 8 + 15);

      // switch (rot1.counter())
      switch (1)
      {
      case 0:
        // pixels = pride(pixels, 96 + 24, deltams);
        break;
      case 1:
        // clear pixels
        FastLED.clear();
        pixels[LexC2I[std::make_pair(rot1.value(), rot2.value())]] = 0xffffff;
        Serial.print(rot1.value());
        Serial.print(", ");
        Serial.print(rot2.value());
        Serial.print(", ");
        Serial.println(LexC2I[std::make_pair(rot1.value(), rot2.value())]);

        // rainbow();
        break;
      case 2:
        pacifica(pixels, TOTAL_NUM_LEDS_VISIBLE);
        // pulse();
        break;
      case 3:
        // colorWipe();
        break;
      case 4:
        // theaterChase(); // no idea what this is
        break;
      case 5:
        // rain();
        break;
      case 6:
        // lixagonChase();
        break;
      }
    }
  }

  // Update LEDs
  for (int i = 0; i < TOTAL_NUM_LEDS_VISIBLE; i++)
  {
    leds[projectionMask.at(i)] = pixels[i];
  }

  // Apply updates
  FastLED.show();
  delay(100);
}