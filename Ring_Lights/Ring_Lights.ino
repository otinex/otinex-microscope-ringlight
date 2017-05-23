#include <FastLED.h>

#define LED_PIN     1
#define NUM_LEDS    16
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define TURNING_PIN 2
#define INTENSITY_PIN 3
#define MODE_BTN 0

CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

void setup() {
  delay(1000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
  }
}


void loop()
{

  int brightness = map(analogRead(INTENSITY_PIN),0, 1023, 255, 0);
  FastLED.setBrightness(brightness);

  FastLED.show();
  //FastLED.delay(1000 / UPDATES_PER_SECOND);
}


void setBrightness(uint8_t brightness) {
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB(brightness, brightness, brightness);
  }
}

