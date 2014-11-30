#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#define PIN 5
#define PIN2 6

//SoftwareSerial mySerial(10, 11); // RX, TX
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

  if(Serial.available()) 
  {
   
   uint8_t degree  = Serial.read(); //incoming serial stream
   degree=(degree/2);
  /* Serial.print(degree);

   // turnoff(); 
    //colorSeg(strip.Color(degree,0,255-degree),  degree, 5);
   // lastdeg=degree;
   //colorSeg(strip.Color(0,0,0),  lastdeg, 3);

   
  
  // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = degree; 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;                           

  // calculate the average:
  average = total / numReadings;         
  // send it to the computer as ASCII digits
  Serial.println(average);   */
  rawData1 = degree;                       // read sensor 1
  degree = digitalSmooth(rawData1, sensSmoothArray1);  // every sensor you use with digitalSmooth needs its own array

     

  if(degree>degreeold){
     jump= ((degree - degreeold)/10) +1;
    for(int i= degreeold; i <= degree; i+=jump){
      //turnoff(); 
      
      colorSeg(strip.Color(i,0,255-i),  i, 5);
      //delay(1);
      //delay(1);        // delay in between reads for stability            
    }
  }


  if(degree<degreeold){
     jump= ((degreeold -degree)/10) +1;

    for(int i= degreeold; i >= degree; i-=jump){
     // turnoff(); 

      colorSeg(strip.Color(i,0,255-i),  i, 5);
   //   delay(1);
      //delay(1);        // delay in between reads for stability            
    }
  }

degreeold=degree;

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



