#include "Polar.h"
#include "LexMap.h"
#include "Arduino.h"

// Maps the (0-41) range to smaller ranges based on radius (r)
const int radmap[4][7]{
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 2, 2},
    {0, 1, 1, 2, 3, 3, 4},
    {0, 1, 2, 3, 4, 5, 6}};
//DOES NOT ACCEPT NEGATIVE RADIUS
int thetaMap(int r, int theta)
{   
    r = r % 4;
    int sign = 1; // 1 for positive, -1 for negative
    if (theta < 0)
    {
        theta = -theta;
        sign = -sign;
    }
    return sign * (((r * 2 + 1) * (theta / 7)) + radmap[r][theta % 7]);
}

// Returns the index of the pixel based on a starting point (x, y), a radius (0-3), and an angle (0-5). (0-17), (0-29), (0-41)
// radius and theta 0 is gaurenteed to retun the same pixel
int polar(int r, int theta, int x = 1, int y = 4)
{
    r = ((r%4)+4) % 4;

    if (r == 0)
    {   
        // Wrap around respecting negatives
        theta = ((theta%6)+6) % 6;
        if (theta < 3)
        {
            x = x - theta;
            y = y;
        }
        else if (theta < 6)
        {
            x = x - 5 + theta;
            y = y - 1;
        }
    }
    else if (r == 1)
    {   
        theta = ((theta%18)+18) % 18;
        // Theta used for calculations based on side length
        int t = theta % 3;
        if (theta < 3)
        {
            x = x + 2 - (t - t / 2);
            y = y + t / 2;
        }
        else if (theta < 6)
        {
            x = x - t;
            y = y + 1;
        }
        else if (theta < 9)
        {
            x = x - 3 - t / 2;
            y = y + 1 - (t - t / 2);
        }
        else if (theta < 12)
        {
            x = x - 4 + (t - t / 2);
            y = y - 1 - t / 2;
        }
        else if (theta < 15)
        {
            x = x - 2 + t;
            y = y - 2;
        }
        else if (theta < 18)
        {
            x = x + 1 + t / 2;
            y = y - 2 + (t - t / 2);
        }
    }
    else if (r == 2)
    {
        theta = ((theta%30)+30) % 30;
        // Theta used for calculations based on side length
        int t = theta % 5;
        if (theta < 5)
        {
            x = x + 4 - (t - t / 2);
            y = y + t / 2;
        }
        else if (theta < 10)
        {
            x = x + 1 - t;
            y = y + 2;
        }
        else if (theta < 15)
        {
            x = x - 4 - t / 2;
            y = y + 2 - (t - t / 2);
        }
        else if (theta < 20)
        {
            x = x - 6 + (t - t / 2);
            y = y - 1 - t / 2;
        }
        else if (theta < 25)
        {
            x = x - 3 + t;
            y = y - 3;
        }
        else if (theta < 30)
        {
            x = x + 2 + t / 2;
            y = y - 3 + (t - t / 2);
        }

        //(theta - theta / 2); // stepper function //011
        //(theta / 2);             // 001
    }
    else if (r == 3)
    {
        theta = ((theta%42)+42) % 42;
        // Theta used for calculations based on side length
        int t = theta % 7;
        if (theta < 7)
        {
            x = x + 6 - (t - t / 2);
            y = y + t / 2;
        }
        else if (theta < 14)
        {
            x = x + 2 - t;
            y = y + 3;
        }
        else if (theta < 21)
        {
            x = x - 5 - t / 2;
            y = y + 3 - (t - t / 2);
        }
        else if (theta < 28)
        {
            x = x - 8 + (t - t / 2);
            y = y - 1 - t / 2;
        }
        else if (theta < 35)
        {
            x = x - 4 + t;
            y = y - 4;
        }
        else if (theta < 42)
        {
            x = x + 3 + t / 2;
            y = y - 4 + (t - t / 2);
        }
    }
    
    return LexC2I(x, y);
}