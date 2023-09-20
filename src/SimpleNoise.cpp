#include "Patterns.h"

void SimpleNoise(CRGB pixels[], int numLeds, int hue, int saturation, std::map<std::pair<int, int>, int> LexC2I, std::map<std::pair<int, int>, int> LixC2I)
{
    const int scale = 100;
    const int speed = 8; //inverted. more is slower
    int v;
    for (int y = 0; y < 8; y++)
    {
        const int width[8] = {4, 5, 6, 7, 7, 6, 5, 4}; // Clearer to to hardcode this vs a loop
        for (int x = -width[y]; x <= width[y]; x++)
        {   
            v = inoise8(x*scale, y*scale, millis()/speed);
            pixels[LexC2I[std::make_pair(x, y)]] = CHSV(hue, saturation, v);
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 24; j++)
        {   
            v = inoise8(i*24*scale, j*scale/4, millis()/speed);
            pixels[LixC2I[std::make_pair(i, j)]] = CHSV(hue, saturation, v);
        }
    }
}