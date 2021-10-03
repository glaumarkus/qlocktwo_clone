#include <FastLED.h>

/*
 * consts
 */
 
#define NUM_LEDS 94  
#define DATA_PIN 13

constexpr int R_VAL = 100;
constexpr int G_VAL = 100;
constexpr int B_VAL = 100;

static CRGB leds[NUM_LEDS];

namespace LED {
  
  void setup_control()
  {
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  }
  
  void turnOnLED(const int& LED_ID)
  {
    leds[LED_ID].setRGB(R_VAL, G_VAL, B_VAL);
    FastLED.show();
  }
  
  void turnOffLED(const int& LED_ID)
  {
   leds[LED_ID] = CRGB::Black;
    FastLED.show();
  } 

  void integrationTest()
  {
    for (int i=0;i<NUM_LEDS;i++)
    {
      turnOnLED(i);
      delay(10);
      turnOffLED(i);
      delay(10);
      }
  }
  
}
