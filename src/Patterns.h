#ifndef PATTERNS_H
#define PATTERNS_H

#include <cstdint>
#include "Arduino.h"
#define FASTLED_INTERNAL
#include "FastLED.h"
#include "Polar.h"
#include "LexMap.h"

using namespace std;

void RayBeam(CRGB pixels[], int angle, int hue = 0, int satuation = 0, int value = 255);

void Pride(CRGB pixels[]);
void Pacifica(CRGB pixels[]);
void RadialPulse(CRGB pixels[], int hue, int saturation);
void SimpleNoise(CRGB pixels[], int hue, int saturation);
void Twinkle(CRGB pixels[], int hue, int saturation);

#endif