// passes RGB info from serial to WS2012(neopixel) strip

#include <Adafruit_NeoPixel.h>
#define PIN 6 //output to led strip
#define Lenght 120

int pos = 0;
int red[Lenght];   // for incoming red color value
int green[Lenght]; // for incoming green color value
int blue[Lenght];  // for incoming blue color value

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Lenght, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Serial.begin(19200); //setup Serial
	strip.begin(); //setup led strip
	strip.show();
  Serial.setTimeout(50);
}

void loop() 
{
  	  // if there's any serial available, read it:
  if(Serial.available() > 0) 
  {
      // look for the next valid integer in the incoming serial stream:
    pos = Serial.parseInt();  // do it again:
    red[pos] = Serial.parseInt();   // do it again:
    green[pos] = Serial.parseInt();   // do it again:
    blue[pos] = Serial.parseInt();   // do it again:
  }

  for(int n=1; n < Lenght; n++)
  {
    strip.setPixelColor(n, red[n], green[n], blue[n]); 
  }
  strip.show();
}