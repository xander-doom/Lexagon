#include "FastLED.h"
#include "ArxContainer.h"
 
#define DATA_PIN    5
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define LEXAGON_NUM_LEDS    96
#define LIXAGON_NUM_LEDS    41
#define BRIGHTNESS  255
 
CRGB leds[LEXAGON_NUM_LEDS];
arx::map<arx::pair<int, int>, int> coord2idx;
arx::map<int, arx::pair<int, int>> idx2coord;

void setup() {
  Serial.begin(115200);
  delay(500); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, LEXAGON_NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // Map the coordinates to the index of the LEDs
  int idx_lastrow = LEXAGON_NUM_LEDS;
  // Bottom to top
  for (int y = 0; y < 8; y++) {
    // Left to right
    int width[8] = {4, 5, 6, 7, 7, 6, 5, 4};
    for (int x = -width[y]; x <= width[y]; x++) {

      int idx;
      if (y%2 == 0) {
        idx = idx_lastrow - x - width[y] - 1;
      } else {
        idx = idx_lastrow + x - width[y] - 1;
      }
      
      coord2idx[arx::make_pair(x, y)] = idx;
      idx2coord[idx] = arx::make_pair(x, y);

      Serial.print(idx2coord[idx].first);
      Serial.print(", ");
      Serial.print(idx2coord[idx].second);
      Serial.print(", ");

      Serial.println(coord2idx[arx::make_pair(x,y)]);

      // Serial.print(x);
      // Serial.print(", ");
      // Serial.print(y);
      // Serial.print(", ");
      // Serial.println(idx);

      leds[idx] = CRGB::White;
      FastLED.show();
      FastLED.delay(25);
    }

    idx_lastrow -= width[y] * 2 + 1;
  }


  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}
 
void loop()
{
  pride();
  FastLED.show();  
}
 
// This function draws rainbows with an ever-changing,
// widely-varying set of parameters.
void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);
 
  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < LEXAGON_NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
 
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
 
    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (LEXAGON_NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}