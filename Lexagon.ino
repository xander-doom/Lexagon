#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <map>
#include <utility>
#include "Rotary.h"
#include "Potentiometer.h"

#define LED_PIN 5
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define LEXAGON_NUM_LEDS 96
#define LIXAGON_NUM_LEDS 41
#define TOTAL_NUM_LEDS LEXAGON_NUM_LEDS + LIXAGON_NUM_LEDS * 6

// Configure LEDs
Adafruit_NeoPixel pixels(TOTAL_NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Coordinate to Index and Index to Coordinate maps
// Coordinate system is custom
// Lexagon uses a cartesian coordinate system with 0,0 in the center middle
// Lixagon uses two circular coordinates, one for which Lixagon and one for which LED (out of 6 and 24 respectively)
std::map<std::pair<int, int>, int> LexC2I;
std::map<int, std::pair<int, int>> LexI2C;
std::map<std::pair<int, int>, int> LixC2I;
std::map<int, std::pair<int, int>> LixI2C;
// Projection of normal LED index onto Lexagon and Lixagon (skip hidden LEDs in Lixagon)
// Used for mapping existing LED patterns to Lexagon
int LEDProjection[TOTAL_NUM_LEDS];

// Potentiometers
Potentiometer pot1;
Potentiometer pot2;

// Rotary encoders
Rotary rot1;
Rotary rot2;

void setup()
{
  // Initialize LEDs
  pixels.begin();
  pixels.clear();

  // Potentiometer connections
  pot1.init(0);
  pot2.init(1);

  // Rotary encoder connections
  rot1.init(2, 11, 10);
  rot2.init(3, 9, 4);

  Serial.begin(115200);

  /**
   ** Initialize the coordinate mapping for LEXAGON **
   */
  // Map the coordinates to the index of the LEDs
  int idx_lastrow = LEXAGON_NUM_LEDS;
  // Bottom to top
  for (int y = 0; y < 8; y++)
  {
    // Left to right
    int width[8] = {4, 5, 6, 7, 7, 6, 5, 4};
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
      LEDProjection[idx] = idx;

      // Todo add power on animation?
    }

    // Update row index
    idx_lastrow -= width[y] * 2 + 1;
  }

  /**
   ** Initialize the coordinate mapping for LIXAGON **
   */

  // Clockwise around the hexes, starting at the bottom
  int idx = LEXAGON_NUM_LEDS;
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

          LEDProjection[i * 24 + r] = idx;
          r++;
        }

        idx++;

        if (j == 6 && k == 2)
          break;
      }
    }
  }
}

int lightMode = 0;
int lastEncoderChange = 9999;
const int menuTimeout = 5000;
const int fadeTime = 300;

void loop()
{

// Check for potentiometer changes
pot1.update();
pot2.update();

// Check for encoder changes
rot1.update();
rot2.update();

  // if (lastEncoderChange < millis() - menuTimeout)
  if (false)
  {
  }
  else
  {
    // switch (rot1.counter())
    switch (0)
    {
    case 0:
      pixels.setPixelColor(0, pot1.value(), (pot1.value()+pot2.value())/2, pot2.value());
      // pride();
      break;
    case 1:
      // rainbow();
      break;
    case 2:
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

  pixels.show();
}