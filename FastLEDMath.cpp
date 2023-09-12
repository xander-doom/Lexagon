#include <Arduino.h>
#include "FastLEDMath.h"

int16_t sin16_C( uint16_t theta )
{
    static const uint16_t base[] =
    { 0, 6393, 12539, 18204, 23170, 27245, 30273, 32137 };
    static const uint8_t slope[] =
    { 49, 48, 44, 38, 31, 23, 14, 4 };

    uint16_t offset = (theta & 0x3FFF) >> 3; // 0..2047
    if( theta & 0x4000 ) offset = 2047 - offset;

    uint8_t section = offset / 256; // 0..7
    uint16_t b   = base[section];
    uint8_t  m   = slope[section];

    uint8_t secoffset8 = (uint8_t)(offset) / 2;

    uint16_t mx = m * secoffset8;
    int16_t  y  = mx + b;

    if( theta & 0x8000 ) y = -y;

    return y;
}

uint16_t scale16( uint16_t i, fract16 scale )
{   
    return ((uint32_t)(i) * (1+(uint32_t)(scale))) / 65536;
}

uint16_t beat88( accum88 beats_per_minute_88, uint32_t timebase, uint32_t time)
{
    return (((time) - timebase) * beats_per_minute_88 * 280) >> 16;
}

uint16_t beatsin88( accum88 beats_per_minute_88, uint16_t lowest, uint16_t highest,
                              uint32_t timebase, uint32_t time, uint16_t phase_offset)
{   
    uint16_t beat = beat88( beats_per_minute_88, timebase, time);
    uint16_t beatsin = (sin16( beat + phase_offset) + 32768);
    uint16_t rangewidth = highest - lowest;
    uint16_t scaledbeat = scale16( beatsin, rangewidth);
    uint16_t result = lowest + scaledbeat;
    return result;
}

uint8_t blend8( uint8_t a, uint8_t b, uint8_t amountOfB)
{
    uint16_t partial;
    uint8_t result;

    partial = (a << 8) | b; // A*256 + B

    // on many platforms this compiles to a single multiply of (B-A) * amountOfB
    partial += (b * amountOfB);
    partial -= (a * amountOfB);

    result = partial >> 8;
    
    return result;
}

//Todo delete this
void printHex32(uint32_t n) {
  char hexChar[8];

  sprintf(hexChar, "%08X ", n);
  Serial.println(hexChar);
}

void printHex8(uint8_t n) {
  char hexChar[2];

  sprintf(hexChar, "%02X ", n);
  Serial.print(hexChar);
}