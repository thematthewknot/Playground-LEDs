#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define PIN 5
#define PIN2 6

uint8_t red =0;
uint8_t green=255;
uint8_t blue =0;

int state = 0;

int jump=0;
uint8_t degreeold=0;
uint8_t oldlocation=0; 
#define SensorPin1      0
#define filterSamples   3              // filterSamples should  be an odd number, no smaller than 3
int sensSmoothArray1 [filterSamples];   // array for holding raw sensor values for sensor1 

int rawData1, smoothData1;  // variables for sensor1 data


Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(120, PIN2, NEO_GRB + NEO_KHZ800);



/*
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;
*/
void setup()
{
  Serial.begin(9600); //setup Serial
 // Serial.setTimeout(10);

  //Setup Strip 1
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255); //Setup global brightness

  //Setup Strip 2
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip2.setBrightness(255); //Setup global brightness


  // initialize serial communication with computer:
  Serial.begin(9600);                   
  // initialize all the readings to 0: 
  //for (int thisReading = 0; thisReading < numReadings; thisReading++)
  //  readings[thisReading] = 0;          
}

void loop() {

if(Serial.available() && state==0) 
{
   
   uint8_t degree  = Serial.read(); //incoming serial stream
   if (degree== 255)
   {
    state = 1;

   }
  if(state==0){
     degree=(degree/2);
    
    rawData1 = degree;                       // read sensor 1
    degree = digitalSmooth(rawData1, sensSmoothArray1);  // every sensor you use with digitalSmooth needs its own array

       

    if(degree>degreeold){
       jump= ((degree - degreeold)/10) +1;
      for(int i= degreeold; i <= degree; i+=jump){
        //turnoff(); 
        
        //colorSeg(strip.Color(i,0,255-i),  i, 5);
        colorSeg(strip.Color(red,green,blue),  i, 5);
        //delay(1);
        //delay(1);        // delay in between reads for stability            
      }
  }

    if(degree<degreeold){
     jump= ((degreeold -degree)/10) +1;

    for(int i= degreeold; i >= degree; i-=jump){
     // turnoff(); 

      colorSeg(strip.Color(red,green,blue),  i, 5);
   //   delay(1);
      //delay(1);        // delay in between reads for stability            
    }
  }

degreeold=degree;
}

if(state==1)
{
 // if(Serial.available()) 
  { 
    while(!Serial.available())
    {

    }
     Serial.print("Entering state 1:");
    
    uint8_t infeed  = Serial.read(); //incoming serial stream
    Serial.println(infeed);
    if (infeed== 1)
    {Serial.println(" listening for RGB");
      while(!Serial.available())
    {

    }
       red  = Serial.read();
         while(!Serial.available())
    {

    }
       green  = Serial.read();
         while(!Serial.available())
    {

    }
       blue  = Serial.read();
      state=0;
    }
    if(infeed==2)
    {Serial.println("starting rainbow");
      rainbow(20);
      turnoff();
     strip.show();
     strip2.show();
      state=0;

    }
    else
    {
      Serial.print("Returning to state 0 value:");
      Serial.println(infeed);
      state=0;
    }

  }


}



  




}
}




int digitalSmooth(int rawIn, int *sensSmoothArray){     // "int *sensSmoothArray" passes an array to the function - the asterisk indicates the array name is a pointer
  int j, k, temp, top, bottom;
  long total;
  static int i;
 // static int raw[filterSamples];
  static int sorted[filterSamples];
  boolean done;

  i = (i + 1) % filterSamples;    // increment counter and roll over if necc. -  % (modulo operator) rolls over variable
  sensSmoothArray[i] = rawIn;                 // input new data into the oldest slot

  // Serial.print("raw = ");

  for (j=0; j<filterSamples; j++){     // transfer data array into anther array for sorting and averaging
    sorted[j] = sensSmoothArray[j];
  }

  done = 0;                // flag to know when we're done sorting              
  while(done != 1){        // simple swap sort, sorts numbers from lowest to highest
    done = 1;
    for (j = 0; j < (filterSamples - 1); j++){
      if (sorted[j] > sorted[j + 1]){     // numbers are out of order - swap
        temp = sorted[j + 1];
        sorted [j+1] =  sorted[j] ;
        sorted [j] = temp;
        done = 0;
      }
    }
  }

/*
  for (j = 0; j < (filterSamples); j++){    // print the array to debug
    Serial.print(sorted[j]); 
    Serial.print("   "); 
  }
  Serial.println();
*/

  // throw out top and bottom 15% of samples - limit to throw out at least one from top and bottom
  bottom = max(((filterSamples * 15)  / 100), 1); 
  top = min((((filterSamples * 85) / 100) + 1  ), (filterSamples - 1));   // the + 1 is to make up for asymmetry caused by integer rounding
  k = 0;
  total = 0;
  for ( j = bottom; j< top; j++){
    total += sorted[j];  // total remaining indices
    k++; 
    // Serial.print(sorted[j]); 
    // Serial.print("   "); 
  }

//  Serial.println();
//  Serial.print("average = ");
//  Serial.println(total/k);
  return total / k;    // divide by number of samples
}

void turnoff() {

  for(uint16_t i=0; i<120; i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
     strip2.setPixelColor(i, strip.Color(0,0,0));
  }
  

  //for(uint16_t i=0; i<120; i++) {
     
      
 // }
 
}

//short segment of moving color
void colorSeg(uint32_t color, uint8_t location, uint32_t seg) {







  for(int n=oldlocation; n<oldlocation+seg; n++) {
      strip.setPixelColor(n, strip.Color(0,0,0));
     strip2.setPixelColor(n, strip.Color(0,0,0));
  }
  for(uint16_t i=location; i<location+seg; i++) {

      strip.setPixelColor(i, color);
      strip2.setPixelColor(i, color);
  }
  strip.show();
  //for(uint16_t i=location; i<location+seg; i++) {
     
      
//  }
  strip2.show();

oldlocation=location;
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
       strip2.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
     strip2.show();
    delay(wait);
  }
}

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


/*#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define PIN 5
#define PIN2 6

SoftwareSerial mySerial(10, 11); // RX, TX




Adafruit_NeoPixel strip = Adafruit_NeoPixel(120, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(120, PIN2, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600); //setup Serial
 // Serial.setTimeout(10);

  //Setup Strip 1
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255); //Setup global brightness

  //Setup Strip 2
  strip2.begin();
  strip2.show(); // Initialize all pixels to 'off'
  strip2.setBrightness(255); //Setup global brightness


  mySerial.begin(9600);
  

}

void loop() 
{
  //byte inputbyte[1];
char lastdeg;
  if(Serial.available()) 
  {
   
   uint8_t degree  = Serial.read(); //incoming serial stream
   degree=(degree/2);
   Serial.print(degree);

    turnoff(); 
    colorSeg(strip.Color(degree,0,255-degree),  degree, 5);
   // lastdeg=degree;
   //colorSeg(strip.Color(0,0,0),  lastdeg, 3);

   
  } 
  
 //if(Serial.available() ) 
 // {
      // look for the next valid integer in the incoming serial stream:
 //   pos = Serial.parseInt();  // do it again:
 //   red[pos] = Serial.parseInt();   // do it again:
 //   green[pos] = Serial.parseInt();   // do it again:
 //   blue[pos] = Serial.parseInt();   // do it again:
 
 // strip.setPixelColor(pos, (int)red[pos], (int)green[pos], (int)blue[pos]); 

//colorSeg((0,255,0), 7, 5);
//colorSeg((0,0,255),  21, 5);
   
//colorSeg((0,0,255),  21, 5);
 // }
//strip.setPixelColor(21, 255,0,0);

  //strip.show();
//  colorSeg(strip.Color(255,255,0),  21, 5);/
//delay(250);
 // colorSeg(strip.Color(255,0,0),  2, 35);
//delay(250);

//delay(250);
}


void turnoff() {

  for(uint16_t i=0; i<120; i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
    
  }
  

  for(uint16_t i=0; i<120; i++) {
      strip2.setPixelColor(i, strip.Color(0,0,0));
      
  }
 
}

//short segment of moving color
void colorSeg(uint32_t color, uint8_t location, uint32_t seg) {

  for(uint16_t i=location; i<location+seg; i++) {
      strip.setPixelColor(i, color);
    
  }
  strip.show();
  for(uint16_t i=location; i<location+seg; i++) {
      strip2.setPixelColor(i, color);
      
  }
  strip2.show();
}




/* 

void colorSeg(uint32_t c, uint8_t location, uint32_t seg) {

  for(uint16_t i=location; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.setPixelColor(i-seg,(0,0,0));
      strip.show();
  }

  for(uint16_t i=location; i<strip.numPixels(); i++) {
      strip2.setPixelColor(i, c);
      strip2.setPixelColor(i-seg,(0,0,0));
      strip2.show();
  }
}






// if there's any serial available, read it:
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