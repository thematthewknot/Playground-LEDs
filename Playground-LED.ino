// passes RGB info from serial to WS2012(neopixel) strip

#include <Adafruit_NeoPixel.h>
#define PIN 6 //output to led strip
#define Lenght 120

int pos = 0;
long red[Lenght];   // for incoming red color value
long green[Lenght]; // for incoming green color value
long blue[Lenght];  // for incoming blue color value

Adafruit_NeoPixel strip = Adafruit_NeoPixel(Lenght, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Serial.begin(9600); //setup Serial
	strip.begin(); //setup led strip
	strip.show();
  Serial.setTimeout(10);
}

void loop() 
{

 if(Serial.available() ) 
  {
      // look for the next valid integer in the incoming serial stream:
    pos = Serial.parseInt();  // do it again:
    red[pos] = Serial.parseInt();   // do it again:
    green[pos] = Serial.parseInt();   // do it again:
    blue[pos] = Serial.parseInt();   // do it again:
 
  strip.setPixelColor(pos, (int)red[pos], (int)green[pos], (int)blue[pos]); 
  Serial.print(pos);
  Serial.print(",");
  Serial.print(red[pos]);
  Serial.print(",");
  Serial.print(green[pos]);
  Serial.print(",");
  Serial.println(blue[pos]);
  }


  strip.show();
}

/* // if there's any serial available, read it:
  if(Serial.available() > 0) 
  {
      // look for the next valid integer in the incoming serial stream:
    pos = Serial.parseInt();  // do it again:
    red[pos] = Serial.parseInt();   // do it again:
    green[pos] = Serial.parseInt();   // do it again:
    blue[pos] = Serial.parseInt();   // do it again:
    Serial.print(pos);
    Serial.print( ",");
    Serial.println(red[pos]); 
  }

  for(int n=1; n < Lenght; n++)
  {
    strip.setPixelColor(n, red[n], green[n], blue[n]); 
  }
  strip.show(); 
} */