#ifndef LEXMAP_H
#define LEXMAP_H

#define LEXAGON_NUM_LEDS 96
#define LIXAGON_NUM_LEDS 41
#define LIXAGON_NUM_LEDS_VISIBLE 24
#define TOTAL_NUM_LEDS 342         // LEXAGON_NUM_LEDS + LIXAGON_NUM_LEDS * 6
#define TOTAL_NUM_LEDS_VISIBLE 240 // LEXAGON_NUM_LEDS + LIXAGON_NUM_LEDS_VISIBLE * 6

struct Coord
{
    int x;
    int y;

    Coord()
    {
        x = 0;
        y = 0;
    }

    Coord(int X, int Y)
    {
        x = X;
        y = Y;
    }
};

int LexC2I(int x, int y);
Coord LexI2C(int idx);
int LixC2I(int hex, int why);
Coord LixI2C(int idx);
int projectionMask(int idx);

#endif