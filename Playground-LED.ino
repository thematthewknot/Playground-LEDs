



// passes RGB info from serial to WS2012(neopixel) strip

#include <Adafruit_NeoPixel.h>

#define PIN 6 //output to led strip
#define Lenght 120

//int incomingByte = 0; // for incoming serial data
int pos = 0;
int red[Lenght];   // for incoming red color value
int green[Lenght]; // for incoming green color value
int blue[Lenght];  // for incoming blue color value
/*
char text;
char hold;
*/



Adafruit_NeoPixel strip = Adafruit_NeoPixel(Lenght, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{

  	Serial.begin(19200); //setup Serial

	strip.begin(); //setup led strip
	strip.show();
Serial.print("this is a test");

}

void loop() 
{



	  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
     pos = Serial.parseInt();  // do it again:
     red[pos] = Serial.parseInt();   // do it again:
     green[pos] = Serial.parseInt();   // do it again:
     blue[pos] = Serial.parseInt();   // do it again:

    // look for the newline. That's the end of your
    // sentence:
   //if (Serial.read() == '/n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
     // red = 255 - constrain(red, 0, 255);
    //  green = 255 - constrain(green, 0, 255);
     // blue = 255 - constrain(blue, 0, 255);

      // fade the red, green, and blue legs of the LED: 
     // analogWrite(redPin, red);
     // analogWrite(greenPin, green);
     // analogWrite(bluePin, blue);

      // print the three numbers in one string as hexadecimal:
      /*
      Serial.print("Position:");
      Serial.println(pos, HEX);
      Serial.print("Red:");
      Serial.println(red, HEX);
      Serial.print("Green:");
      Serial.println(green, HEX);
      Serial.print("Blue:");
      Serial.println(blue, HEX);
      */


//}

}

for(int n=1; n < Lenght; n++)
{
strip.setPixelColor(n, red[n], green[n], blue[n]);
 //red[n] = 0;
 //green[n] = 0;
 //blue[n] = 0;
}
strip.show();


//    }
  



/*
	 while(Serial.available() > 0){
    
    if(index < 9) // One less than the size of the array
    {
      inByte = Serial.read(); // Read a Byte
      inData[index] = inByte; // Store it
      index++; 
       
       // digitalWrite(ledPin, HIGH);
    
     //   digitalWrite(ledPin, LOW);
        Serial.println(inData[1]);
        Serial.println(inData[2]);
        Serial.println(inData[3]);
        Serial.println(inData[4]);
        Serial.println(inData[5]);
        Serial.println(inData[6]);
        Serial.println(inData[7]);
        Serial.println(inData[8]);
        Serial.println(inData[9]);        
        }
   		 }
 	
*/

	//while(true){
	/*	if(Serial.available() > 0)
		{    
				// read the incoming byte:
              //  incomingByte = Serial.read();
                red = Serial.readBytes((char*)hold, 1);
                green = Serial.readBytes((char*)hold, 1);
                blue = Serial.readBytes((char*)hold, 1);
                // say what you got:
                Serial.print("red: ");
                Serial.println(red, DEC);
                 Serial.print("green: ");
                Serial.println(green, DEC);
                 Serial.print("blue: ");
                Serial.println(blue, DEC);

		}*/


//	}
	

}