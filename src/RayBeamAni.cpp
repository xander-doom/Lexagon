#include "Patterns.h"

// Angle is between 0 and 255
void RayBeamAni(CRGB pixels[], int angle, int hue = 0, int satuation = 0, int value = 255)
{
    const float width = 3.0;

    float a = sin8(angle) / 255.0;
    float b = cos8(angle) / 255.0;

    //cos/3, c = -2 looks sick

    for (int i = 0; i < LEXAGON_NUM_LEDS; i++)
    {
        int x = LexI2C(i).x;
        int y = LexI2C(i).y;

        //Distance calculation (very simple since numbers are normalized)
        float d = a * x + b * y;

        if (d > width){
            pixels[i] = CRGB::Black;
        } else {
            int v = 255.0 * d / 3.0;
            pixels[i] = CHSV(hue, satuation, v);
        }
    }
}