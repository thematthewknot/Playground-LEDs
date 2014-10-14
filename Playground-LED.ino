// passes RGB info from serial to WS2012(neopixel) strip

#include <Adafruit_NeoPixel.h>

#define PIN 6 //output to led strip

int incomingByte = 0; // for incoming serial data

void setup() 
{

  	Serial.begin(9600); //setup Serial

	strip.begin(); //setup led strip
	strip.show();

}

void loop() 
{
	while(true){
		if(Serial.available() > 0)
		{    
				// read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);

		}
	}
	

}