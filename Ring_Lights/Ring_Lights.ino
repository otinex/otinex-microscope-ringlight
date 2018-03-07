#include <FAB_LED.h>
#include <Button.h>

#define LED_PIN     1
#define NUM_LEDS    16
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define TURNING_PIN A1
#define INTENSITY_PIN 3
#define MODE_BTN 0 //Pin 6 on Arduino Mega!!!

sk6812<D, 1> ring;
rgbw leds[NUM_LEDS] = {};
Button button = Button(MODE_BTN,BUTTON_PULLDOWN);
bool LastButtonState = false, transition = false;;
typedef enum mode {normalMode, movingMode, offMode} mode_t;
int ButonState = false;
int avgfac = 100;

void setup() {

  pinMode(MODE_BTN, INPUT);

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

  switch (mode)
  {
     case normalMode: 
	 {
        NormalMode();
		delay(50);
     }
             break;
     case movingMode:
	 {
        MovingMode();
     }
             break;
	 case offMode: 
	 {
		 OffMode();
		 delay(50);
	 }
			 break;
  }
  LastButtonState = ButtonState;
  delay(10);
  }


void setBrightness(uint8_t brightness) {
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
  leds[i].r = brightness;
	leds[i].g = brightness;
	leds[i].b = brightness;
	leds[i].w = brightness;
  }
}


void MovingMode()
{
  
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    setBrightness(0);
    int brightness = getBrightnessSP();
  for (size_t i = 0; i < 4; i++)
    {
    int idx_ = (getPositionSP() + i)%NUM_LEDS;
    leds[idx_].r = brightness;
    leds[idx_].g = brightness;
    leds[idx_].b = brightness;
    leds[idx_].w = brightness;
    }
    ring.sendPixels(NUM_LEDS, leds);
  if (transition == true){mode = offMode;}
  transition = false;  
}
}



void NormalMode()
{ 
  setBrightness(getBrightnessSP());
  ring.sendPixels(NUM_LEDS, leds);
  if (transition == true){
    
    mode = movingMode;}
  transition = false;
}

void OffMode()
{
	setBrightness(0);
	ring.sendPixels(NUM_LEDS, leds);
	if (transition == true) { mode = normalMode; }
	transition = false;
}



int getBrightnessSP(){
 int brightness = 0;
  for (size_t i = 0; i < avgfac; i++)
    {
      brightness += map(analogRead(INTENSITY_PIN),0,1023,255,0);
      delayMicroseconds(100);
    }
    return brightness/avgfac;
}

int getPositionSP(){

		int positionOffset = map(analogRead(TURNING_PIN), 0, 1023, 0, 16);
			  
  return positionOffset;
}

