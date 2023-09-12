#ifndef FASTLEDMATH_H
#define FASTLEDMATH_H

#include <cstdint>
#define LIB8STATIC __attribute__ ((unused)) static inline
#define GET_MILLIS millis
#define sin16 sin16_C

//todo remove extras
typedef uint8_t   fract8;
typedef int8_t    sfract7;
typedef uint16_t  fract16;
typedef int16_t   sfract15;
typedef uint16_t  accum88;   
typedef int16_t   saccum78;  
typedef uint32_t  accum1616; 
typedef int32_t   saccum1516;
typedef uint16_t  accum124;  
typedef int32_t   saccum114; 

int16_t sin16_C( uint16_t theta );

uint16_t scale16( uint16_t i, fract16 scale );

uint16_t beat88( accum88 beats_per_minute_88, uint32_t timebase = 0, uint32_t time = 0);

uint16_t beatsin88( accum88 beats_per_minute_88, uint16_t lowest = 0, uint16_t highest = 65535, uint32_t timebase = 0, uint32_t time = 0, uint16_t phase_offset = 0);

uint8_t blend8( uint8_t a, uint8_t b, uint8_t amountOfB);

void printHex32(uint32_t n);

void printHex8(uint8_t n);

#endif