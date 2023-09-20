#ifndef PATTERNS_H
#define PATTERNS_H

#include <cstdint>
#include <vector>
#include "Arduino.h"
#include "FastLED.h"
#include "Polar.h"

using namespace std;

void pride(CRGB leds[], int numLeds);
void pacifica(CRGB leds[], int numLeds);
void RadialPulse(CRGB pixels[], int numLeds, int hue, int saturation, std::map<std::pair<int, int>, int> LexC2I, std::map<std::pair<int, int>, int> LixC2I);
void SimpleNoise(CRGB pixels[], int numLeds, int hue, int saturation, std::map<std::pair<int, int>, int> LexC2I, std::map<std::pair<int, int>, int> LixC2I);

#endif