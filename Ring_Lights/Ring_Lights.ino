#include <FastLED.h>
#include <Button.h>

#define LED_PIN     1
#define NUM_LEDS    16
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define TURNING_PIN A1
#define INTENSITY_PIN 3
#define MODE_BTN 0 //Pin 6 on Arduino Mega!!!


CRGB leds[NUM_LEDS];
Button button = Button(MODE_BTN,BUTTON_PULLDOWN);
bool LastButtonState = false, transition = false;;
typedef enum mode {normalMode, movingMode} mode_t;
int ButonState = false;

void setup() {

  pinMode(MODE_BTN, INPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
  } 
}
mode_t mode = normalMode;

void loop()
{
bool  ButtonState = button.isPressed();
//
if(ButtonState != LastButtonState)
  {
    if (ButtonState == 1)
    {
      transition = true;
    }
  }

  switch (mode){
     case normalMode: {
        NormalMode();
     }
             break;
     case movingMode:{
        MovingMode();         
     }
             break;
  }
  
  FastLED.setBrightness(getBrightnessSP());
  FastLED.show();
  LastButtonState = ButtonState;
}


void setBrightness(uint8_t brightness) {
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i].setRGB(brightness, brightness, brightness);
  }
}


void MovingMode()
{
  
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    if ( i < getPositionSP() || i > getPositionSP() +4)
    {
    leds[i] = CRGB::Black;
    }
    else 
    {
      leds[i] = CRGB::White;
    }
  }
  if (transition == true){mode = normalMode;}
  transition = false;  
}

void NormalMode()
{ 
  for(size_t i = 0; i< NUM_LEDS; i++)
  {
    leds[i] = CRGB::White;
  }
  if (transition == true){mode = movingMode;}
  transition = false;
}

int getBrightnessSP(){
  
  int brightness = map(analogRead(INTENSITY_PIN),0,1023,255,0);
    return brightness;
}

int getPositionSP(){
  int positionOffset = map(analogRead(TURNING_PIN),0,1023,0,16);
  return positionOffset;
}

