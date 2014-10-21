#include <Adafruit_NeoPixel.h>

#define PIN 6
int task = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600); //setup Serial
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {


   if(Serial.available() ) 
  {
      // look for the next valid integer in the incoming serial stream:
    task = Serial.parseInt(); 
  }
  switch (task) {
      case 1: //segment strip wipe
        colorWipeSeg(strip.Color(0, 0, 255), 15, 3);
        break;
      case 2: //segment strip wipe reverse
        colorWipeRevSeg(strip.Color(0,0,255), 15, 3);
        break;
      case 3: //full strip wipe
        colorWipe(strip.Color(0, 255, 0), 15);
        break;
      case 4:  //full strip wipe reversed 
        colorWipeRev(strip.Color(0, 255, 0), 15);
        break;
      case 5: //rainbow
        rainbow(5);
      default: //blank
        blank();
  }

}

// Fill the strip one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

//fills strip in opposeite direction
void colorWipeRev(uint32_t c, uint32_t wait) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i,c);
      strip.show();
      delay(wait);
  }
}

//short segment of moving color
void colorWipeSeg(uint32_t c, uint8_t wait, uint32_t seg) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.setPixelColor(i-seg,(0,0,0));
      strip.show();
      delay(wait);
  }
}

//short segment of moving color opposite direction
void colorWipeRevSeg(uint32_t c, uint32_t wait, uint32_t seg) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i,c);
      strip.setPixelColor(i+seg,(0,0,0));
      strip.show();
      delay(wait);
  }
}

//blank strip
void blank(){
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i,0,0,0);
  }
  strip.show();
}

//rainbow strip
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

