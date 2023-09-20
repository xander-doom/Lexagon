#include "Patterns.h"

void RadialPulse(CRGB pixels[], int numLeds, int hue, int saturation, std::map<std::pair<int, int>, int> LexC2I, std::map<std::pair<int, int>, int> LixC2I){
    EVERY_N_MILLIS_I(refreshRate, 20)
    // if(true)
    {   
        int bri, var; //brightness and variation
        //Lexagon
        for (int i = 0; i < 4; i++){
            //Modulate the brightness of the pulse in the middles.
            bri = beatsin88(1024, 30, 200, 0, i*16384);
            for (int j = 0; j < 42; j++){
                var = beatsin88(8192, 0, 55, 0, i*16384+j*1560);
                pixels[polar(LexC2I, 1, 4, i, thetaMap(i, j))] = CHSV(hue, saturation, bri+var);
            }
        }
        
        //Lixagon (similar)
        for (int i = 0; i < 6; i++){
            //Modulate the brightness of the pulse in the middles.
            bri = beatsin88(1024, 30, 200, 0, i*16384);
            for (int j = 0; j < 24; j++){
                var = beatsin88(8192, 0, 55, 0, i*16384+j*1560);
                pixels[LixC2I[std::make_pair(i, j)]] = CHSV(hue, saturation, bri+var);
            }
        }


        //todo lixagon
    }
}