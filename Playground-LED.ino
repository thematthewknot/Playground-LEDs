// passes RGB info from serial to WS2012(neopixel) strip

#include <Adafruit_NeoPixel.h>


#define PIN 6

void setup() 
{

  	Serial.begin(9600); //setup Serial

	strip.begin(); //setup led strip
	strip.show();

}

void loop() 
{

	

}