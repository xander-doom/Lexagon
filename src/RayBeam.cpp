#include "Patterns.h"

// Angle is between 0 and 65535
void RayBeam(CRGB pixels[], int angle, int hue, int satuation, int value)
{
    const float width = 1.5;

    float a = sin16(angle)/32767.0;
    float b = cos16(angle)/32767.0;

    for (int i = 0; i < LEXAGON_NUM_LEDS; i++)
    {
        int x = LexI2C(i).x;
        int y = LexI2C(i).y;

        //Distance calculation (very simple since numbers are normalized)
        float d = a * x + b * y  - b*3.5; //3.5 is the middle of the lexagon in lexagon coordinates
        d = abs(d);

        if (d > width){
            pixels[i] = CRGB::Black;
        } else {
            int v = 255.0 * d / width;
            //v = 255;
            pixels[i] = CHSV(0, 0, 255-v);
        }
    }
}