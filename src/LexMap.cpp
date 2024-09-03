#include "LexMap.h"

// Everything in this file was calculated by the functions at the bottom.
// Hardcoding them makes access easier between files because static classe shenanigans can be avoided. 

// Coordinate to Index and Index to Coordinate maps
// Coordinate system is custom
// Lexagon uses a cartesian coordinate system with 0,0 in the center middle
// Lixagon uses two circular coordinates, one for which Lixagon and one for which LED (out of 6 and 24 respectively)
// Index does NOT USE THE PROJECTION MAP. PROJECTION MAP IS APPLIED AT THE END

// Projection of normal LED index onto Lexagon and Lixagon (skip hidden LEDs in Lixagon)
// Used for mapping existing LED patterns to Lexagon

// Lexagon Coordinate to Index
const int LexC2Idata[8][15] = {
    {0 , 0 , 0 , 95, 94, 93, 92, 91, 90, 89, 88, 87, 0 , 0 , 0 },
    {0 , 0 , 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 0 , 0 },
    {0 , 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 0 },
    {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62},
    {47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33},
    {0 , 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 0 },
    {0 , 0 , 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9 , 0 , 0 },
    {0 , 0 , 0 , 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 0 , 0 , 0 }
};

// Lexagon Index to Coordinate
const Coord LexI2Cdata[LEXAGON_NUM_LEDS] = {
    {-4, 7},{-3, 7},{-2, 7},{-1, 7},{0 , 7},{1 , 7},{2 , 7},{3 , 7},
    {4 , 7},{5 , 6},{4 , 6},{3 , 6},{2 , 6},{1 , 6},{0 , 6},{-1, 6},
    {-2, 6},{-3, 6},{-4, 6},{-5, 6},{-6, 5},{-5, 5},{-4, 5},{-3, 5},
    {-2, 5},{-1, 5},{0 , 5},{1 , 5},{2 , 5},{3 , 5},{4 , 5},{5 , 5},
    {6 , 5},{7 , 4},{6 , 4},{5 , 4},{4 , 4},{3 , 4},{2 , 4},{1 , 4},
    {0 , 4},{-1, 4},{-2, 4},{-3, 4},{-4, 4},{-5, 4},{-6, 4},{-7, 4},
    {-7, 3},{-6, 3},{-5, 3},{-4, 3},{-3, 3},{-2, 3},{-1, 3},{0 , 3},
    {1 , 3},{2 , 3},{3 , 3},{4 , 3},{5 , 3},{6 , 3},{7 , 3},{6 , 2},
    {5 , 2},{4 , 2},{3 , 2},{2 , 2},{1 , 2},{0 , 2},{-1, 2},{-2, 2},
    {-3, 2},{-4, 2},{-5, 2},{-6, 2},{-5, 1},{-4, 1},{-3, 1},{-2, 1},
    {-1, 1},{0 , 1},{1 , 1},{2 , 1},{3 , 1},{4 , 1},{5 , 1},{4 , 0},
    {3 , 0},{2 , 0},{1 , 0},{0 , 0},{-1, 0},{-2, 0},{-3, 0},{-4, 0}
};

// Lixagon Coordinate to Index
const int LixC2Idata[6][LIXAGON_NUM_LEDS_VISIBLE] = {
    {96 , 97 , 98 , 99 , 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119}, 
    {120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143}, 
    {144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167},
    {168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191},
    {192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215},
    {216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239}
};

// Lixagon Index to Coordinate
const Coord LixI2Cdata[6 * LIXAGON_NUM_LEDS_VISIBLE] = {
    {0, 0 }, {0, 1 }, {0, 2 }, {0, 3 }, {0, 4 }, {0, 5 }, {0, 6 }, {0, 7 }, {0, 8 }, {0, 9 }, {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14}, {0, 15}, {0, 16}, {0, 17}, {0, 18}, {0, 19}, {0, 20}, {0, 21}, {0, 22}, {0, 23},
    {1, 0 }, {1, 1 }, {1, 2 }, {1, 3 }, {1, 4 }, {1, 5 }, {1, 6 }, {1, 7 }, {1, 8 }, {1, 9 }, {1, 10}, {1, 11}, {1, 12}, {1, 13}, {1, 14}, {1, 15}, {1, 16}, {1, 17}, {1, 18}, {1, 19}, {1, 20}, {1, 21}, {1, 22}, {1, 23},
    {2, 0 }, {2, 1 }, {2, 2 }, {2, 3 }, {2, 4 }, {2, 5 }, {2, 6 }, {2, 7 }, {2, 8 }, {2, 9 }, {2, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}, {2, 15}, {2, 16}, {2, 17}, {2, 18}, {2, 19}, {2, 20}, {2, 21}, {2, 22}, {2, 23},
    {3, 0 }, {3, 1 }, {3, 2 }, {3, 3 }, {3, 4 }, {3, 5 }, {3, 6 }, {3, 7 }, {3, 8 }, {3, 9 }, {3, 10}, {3, 11}, {3, 12}, {3, 13}, {3, 14}, {3, 15}, {3, 16}, {3, 17}, {3, 18}, {3, 19}, {3, 20}, {3, 21}, {3, 22}, {3, 23},
    {4, 0 }, {4, 1 }, {4, 2 }, {4, 3 }, {4, 4 }, {4, 5 }, {4, 6 }, {4, 7 }, {4, 8 }, {4, 9 }, {4, 10}, {4, 11}, {4, 12}, {4, 13}, {4, 14}, {4, 15}, {4, 16}, {4, 17}, {4, 18}, {4, 19}, {4, 20}, {4, 21}, {4, 22}, {4, 23},
    {5, 0 }, {5, 1 }, {5, 2 }, {5, 3 }, {5, 4 }, {5, 5 }, {5, 6 }, {5, 7 }, {5, 8 }, {5, 9 }, {5, 10}, {5, 11}, {5, 12}, {5, 13}, {5, 14}, {5, 15}, {5, 16}, {5, 17}, {5, 18}, {5, 19}, {5, 20}, {5, 21}, {5, 22}, {5, 23}
};

// Projection of normal LED index onto Lexagon and Lixagon (skip hidden LEDs in Lixagon)
const int projectionMaskdata[TOTAL_NUM_LEDS_VISIBLE]= {
    0  , 1  , 2  , 3  , 4  , 5  , 6  , 7  , 8  , 9  , 10 , 11 , 12 , 13 , 14 , 15 , 16 , 17 , 18 , 19 , 
    20 , 21 , 22 , 23 , 24 , 25 , 26 , 27 , 28 , 29 , 30 , 31 , 32 , 33 , 34 , 35 , 36 , 37 , 38 , 39 , 
    40 , 41 , 42 , 43 , 44 , 45 , 46 , 47 , 48 , 49 , 50 , 51 , 52 , 53 , 54 , 55 , 56 , 57 , 58 , 59 , 
    60 , 61 , 62 , 63 , 64 , 65 , 66 , 67 , 68 , 69 , 70 , 71 , 72 , 73 , 74 , 75 , 76 , 77 , 78 , 79 , 
    80 , 81 , 82 , 83 , 84 , 85 , 86 , 87 , 88 , 89 , 90 , 91 , 92 , 93 , 94 , 95 , 96 , 98 , 99 , 101, 
    103, 105, 106, 108, 110, 112, 113, 115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 134, 136, 
    137, 139, 140, 142, 144, 146, 147, 149, 151, 153, 154, 156, 158, 160, 161, 163, 165, 167, 168, 170, 
    172, 174, 175, 177, 178, 180, 181, 183, 185, 187, 188, 190, 192, 194, 195, 197, 199, 201, 202, 204, 
    206, 208, 209, 211, 213, 215, 216, 218, 219, 221, 222, 224, 226, 228, 229, 231, 233, 235, 236, 238, 
    240, 242, 243, 245, 247, 249, 250, 252, 254, 256, 257, 259, 260, 262, 263, 265, 267, 269, 270, 272, 
    274, 276, 277, 279, 281, 283, 284, 286, 288, 290, 291, 293, 295, 297, 298, 300, 301, 303, 304, 306, 
    308, 310, 311, 313, 315, 317, 318, 320, 322, 324, 325, 327, 329, 331, 332, 334, 336, 338, 339, 341
};

int LexC2I(int x, int y){
    return LexC2Idata[y][x+7];
}

Coord LexI2C(int idx){
    return LexI2Cdata[idx];
}

int LixC2I(int hex, int why){
    return LixC2Idata[hex][why];
}

Coord LixI2C(int idx){
    return LixI2Cdata[idx+LEXAGON_NUM_LEDS];
}

int projectionMask(int idx){
    return projectionMaskdata[idx];
}

// void initLexMap()
// {
//     /**
//      ** Initialize the coordinate mapping for LEXAGON **
//      */
//     // Map the coordinates to the index of the LEDs
//     int idx_lastrow = LEXAGON_NUM_LEDS;
//     // Bottom to top
//     for (int y = 0; y < 8; y++)
//     {
//         // Left to right
//         int width[8] = {4, 5, 6, 7, 7, 6, 5, 4}; // Clearer to to hardcode this vs a loop
//         for (int x = -width[y]; x <= width[y]; x++)
//         {

//             // Compensate for switchback wiring
//             int idx;
//             if (y % 2 == 0)
//             {
//                 idx = idx_lastrow - x - width[y] - 1;
//             }
//             else
//             {
//                 idx = idx_lastrow + x - width[y] - 1;
//             }

//             // Associate the coordinates with the index both ways
//             LexC2I[x+7][y] = idx;
//             LexI2C[idx] = Coord(x, y);
//             projectionMask[idx] = idx;
//         }

//         // Update row index
//         idx_lastrow -= width[y] * 2 + 1;
//     }
// }

// void initLixMap()
// {
//     /**
//      ** Initialize the coordinate mapping for LIXAGON **
//      */

//     // Clockwise around the hexes, starting at the bottom
//     int idx = LEXAGON_NUM_LEDS;
//     int ledidx = LEXAGON_NUM_LEDS; // led mapping for projection mask
//     for (int i = 0; i < 6; i++)
//     {
//         int r = 0;
//         // Counterclockwise around sides, starting where the wire comes in (first side twice)
//         for (int j = 0; j < 7; j++)
//         {
//             // Along the LEDs on the side
//             for (int k = 0; k < 7; k++)
//             {
//                 if (j == 0 && k == 0) // Start in the middle of the first side
//                     k = 4;

//                 if (k % 2 == 0)
//                 {
//                     // Initalization code goes here
//                     // idx = global index of LED
//                     // i = lixagon
//                     // j = side of lixagon
//                     // k = LED on that side
//                     // r = index of LED in that lixagon
//                     LixC2I[i][r] = idx;
//                     LixI2C[idx] = Coord(i, r);

//                     projectionMask[i * 24 + r + LEXAGON_NUM_LEDS] = ledidx;
//                     r++;

//                     idx++; // Pixel mapping. move outside of the if statment for led mapping.
//                 }
//                 ledidx++; // led mapping for projection mask

//                 if (j == 6 && k == 2)
//                     break;
//             }
//         }
//     }
// }