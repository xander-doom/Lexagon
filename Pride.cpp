#include "Patterns.h"
#include <Adafruit_NeoPixel.h>
#include "FastLEDMath.h"
#include <cstdint>
#include <vector>

using namespace std;

// This function draws rainbows with an ever-changing,
// Widely-varying set of parameters.

vector<uint32_t> pride(vector<uint32_t> &pixels, int numLeds, int deltams)
{
    numLeds = 200;
    static uint16_t sPseudotime = 0;
    static uint16_t sHue16 = 0;
    static uint32_t patternTime = 0;

    uint8_t sat8 = beatsin88(87, 220, 250, patternTime);

    uint8_t brightdepth = beatsin88(341, 96, 224, patternTime);

    uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256), patternTime);

    uint8_t msmultiplier = beatsin88(147, 23, 60, patternTime);

    uint16_t hue16 = sHue16; // gHue * 256;

    uint16_t hueinc16 = beatsin88(113, 1, 3000, patternTime);

    patternTime += deltams;

    sPseudotime += deltams * msmultiplier;

    sHue16 += deltams * beatsin88(400, 5, 9, patternTime);

    uint16_t brightnesstheta16 = sPseudotime;

    for (uint16_t i = 0; i < numLeds; i++)
    {
        hue16 += hueinc16 / 8; // todo calibrate this to taste
        // uint8_t hue8 = hue16 / 256;

        brightnesstheta16 += brightnessthetainc16;
        uint16_t b16 = sin16(brightnesstheta16) + 32768;

        uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
        uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
        bri8 += (255 - brightdepth);

        uint32_t newcolor = Adafruit_NeoPixel::ColorHSV(hue16, sat8, bri8);
        newcolor = Adafruit_NeoPixel::gamma32(newcolor);

        int pixelnumber = i;
        pixelnumber = (numLeds - 1) - pixelnumber;
        // nblend(leds[pixelnumber], newcolor, 64);

        // RED   (uint8_t)(c >> 16);
        // GREEN (uint8_t)(c >>  8);
        // BLUE  (uint8_t)(c >>  0);
        uint8_t red, green, blue;

        red = blend8((uint8_t)(pixels[i] >> 16), (uint8_t)(newcolor >> 16), 64);
        green = blend8((uint8_t)(pixels[i] >> 8), (uint8_t)(newcolor >> 8), 64);
        blue = blend8((uint8_t)(pixels[i] >> 0), (uint8_t)(newcolor >> 0), 64);

        pixels[i] = Adafruit_NeoPixel::Color(red, green, blue);
    }

    return pixels;
}
