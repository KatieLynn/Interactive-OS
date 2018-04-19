//Alpha stage code for final project
//Interactive Objects and Systems Sp'18
//by Katie Pulles

//this code will alter a neopixel pattern depending on 
//how many capacitive sensors are being touched

//include CapSense and Neopixel libraries
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN            2 //pin connected to neopixels on Arduino
#define NUMPIXELS      3 //how many neopixels are in the strip

// Parameters for setting up the NeoPixel library are: 1) how many pixels, 2)which pin to use to send signals,
// 3}pixel type flags that can be added together
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//create four instances of capacitive sensors w/send and receive pins as parameters
CapacitiveSensor sensorA=CapacitiveSensor(3,4); //3 is send pin, 4 is receive
CapacitiveSensor sensorB=CapacitiveSensor(5,6); //5 is send pin, 6 is receive
CapacitiveSensor sensorC=CapacitiveSensor(7,8); //7 is send pin, 8 is receive
CapacitiveSensor sensorD=CapacitiveSensor(9,10); //9 is send pin, 10 is receive



//holds thresholds of sensors (only the first one is really necessary)
int threshold1 = 50;
int threshold2 = 100;  
int threshold3 = 2000; 
//int threshold4 = 10000; //not needed because all four must be touching for it to work and they'll all be above 2k 

void setup() {
  leds.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600); //begin serial monitor to make print statements
  normalBreath(); //put normalBreath in setup so the circuit starts off with this
}

void loop() {
  //long start = millis(); //long variable because milliseconds will grow quickly, begins when function starts running
  long capValA = sensorA.capacitiveSensor(30); //read sensor A
  long capValB = sensorB.capacitiveSensor(30); //read sensor B
  long capValC = sensorC.capacitiveSensor(30); //read sensor C
  long capValD = sensorD.capacitiveSensor(30); //read sensor D
  
//  Serial.print(millis() - start); //prints milliseconds from start 
//  Serial.print("\t"); //tab
  Serial.print(capValA); //prints the value of the sensors w/tabs in between
  Serial.print("\t");
  Serial.print(capValB);
  Serial.print("\t");
  Serial.print(capValC);
  Serial.print("\t");
  Serial.println(capValD);

  //if any one sensor is triggered
  if((capValA>threshold1 && capValB<=threshold1 && capValC<=threshold1 && capValD<=threshold1) ||
  (capValA<=threshold1 && capValB>threshold1 && capValC<=threshold1 && capValD<=threshold1) || 
  (capValA<=threshold1 && capValB<=threshold1 && capValC>threshold1 && capValD<=threshold1) || 
  (capValA<=threshold1 && capValB<=threshold1 && capValC<=threshold1 && capValD>threshold1)) 
  {
  breathPatternA();
  }

  //if any two sensors are triggered
  else if((capValA>threshold2 && capValB>threshold2 && capValC<=threshold2 && capValD<=threshold2) || 
  (capValA>threshold2 && capValB<=threshold2 && capValC>threshold2 && capValD<=threshold2) || 
  (capValA>threshold2 && capValB<=threshold2 && capValC<=threshold2 && capValD>threshold2) || 
  (capValA<=threshold2 && capValB>threshold2 && capValC>threshold2 && capValD<=threshold2) || 
  (capValA<=threshold2 && capValB>threshold2 && capValC<=threshold2 && capValD>threshold2) || 
  (capValA<=threshold2 && capValB<=threshold2 && capValC>threshold2 && capValD>threshold2))
  {
  breathPatternB();
  }

  //if any three sensors are triggered
  else if((capValA>threshold3 && capValB>threshold3 && capValC>threshold3 && capValD<=threshold3) || 
  (capValA>threshold3 && capValB>threshold3 && capValC<=threshold3 && capValD>threshold3) || 
  (capValA>threshold3 && capValB<=threshold3 && capValC>threshold3 && capValD>threshold3) ||
  (capValA<=threshold3 && capValB>threshold3 && capValC>threshold3 && capValD>threshold3))
  {
  breathPatternC();
  }

  //if all four sensors are triggered
  else if(capValA>threshold1 && capValB>threshold1 && capValC>threshold1 && capValD>threshold1)
  {
  breathPatternD();
  }
  
  else
  {
    normalBreath();
  }

}

//normalBreath is for when none of the sensors are triggered, calm breathing pattern 
//w/soothing cool color and not full brightness
void normalBreath()
{
  for(int j=1; j<=100; j++) //j will adjust the pixel brightness
  {
    for(int i=0; i<=NUMPIXELS; i++) //i allows all the pixels to have the same pattern
    {
      leds.setPixelColor(i,leds.Color(0,200,250));
      leds.setBrightness(j);
    }
    leds.show();
    delay(20);
  }

  for(int j=100; j>0; j--)
  {
   
    for(int i=0; i<=NUMPIXELS;i++)
    {
      leds.setPixelColor(i,leds.Color(0,200,250));
      leds.setBrightness(j);
    }
    leds.show();
    delay(30);
  }

}

//for when one of the sensors is triggered, sped up breath pattern and
//colors get hotter, brightness increases
void breathPatternA() 
{
for(int j=1; j<=150; j++) //j will adjust the pixel color and brightness
  {
    for(int i=0; i<=NUMPIXELS; i++) //i allows all the pixels to have the same pattern
    {
      leds.setPixelColor(i,leds.Color(j+100,180,20));
      leds.setBrightness(j);
    }
    leds.show();
    delay(10);
  }

  for(int j=150; j>0; j--)
  {
    for(int i=0; i<=NUMPIXELS;i++)
    {
      leds.setPixelColor(i,leds.Color(j+100,180,20));
      leds.setBrightness(j);
    }
    leds.show();
    delay(10);
  }
}

//for when two sensors are triggered, lights start blinking slowly and color 
//turns yellow-orange, brightness increases
void breathPatternB() 
{
    for(int i=0; i<=NUMPIXELS; i++) //i allows all the pixels to have the same pattern
    {
      leds.setPixelColor(i,leds.Color(255,150,0));
      leds.setBrightness(150);
    }
    leds.show();
    delay(400);
    for(int i=0; i<=NUMPIXELS;i++)
    {
      leds.setPixelColor(i,leds.Color(i,0,0,0));
      leds.setBrightness(150);
    }
    leds.show();
    delay(400);
}

//for when three sensors are triggered, lights blink rapidly and get 
//red, not yet full brightness
void breathPatternC() 
{
  for(int i=0; i<=NUMPIXELS; i++) //i allows all the pixels to have the same pattern
    {
      leds.setPixelColor(i,leds.Color(255,0,0));
      leds.setBrightness(150);
    }
    leds.show();
    delay(200);
    for(int i=0; i<=NUMPIXELS;i++)
    {
      leds.setPixelColor(i,leds.Color(i,0,0,0));
      leds.setBrightness(150);
    }
    leds.show();
    delay(200);
}

//for when all four sensors are triggered, lights on full brightness and white and blinding
void breathPatternD() 
{
  for(int i=0; i<=NUMPIXELS; i++) //i allows all the pixels to have the same pattern
    {
      leds.setPixelColor(i,leds.Color(255, 255,255));
      leds.setBrightness(255);
    }
    leds.show();
}
//BELOW is test for three nested for loops, doesn't work properly
//for(int j=1; j<=150; j++) //j will adjust the pixel color and brightness
//  {
//    for(int k=0; k<=255; k++)
//    {
//    for(int i=0; i<=NUMPIXELS; i++) //i allows all the pixels to have the same pattern
//    {
//      leds.setPixelColor(i,leds.Color(j+100,180,20));
//      leds.setBrightness(k);
//    }
//    }
//    leds.show();
//    delay(10);
//  }
//
//  for(int j=150; j>0; j--)
//  {
//    for(int k=255;k>=0; k--)
//    {
//    for(int i=0; i<=NUMPIXELS;i++)
//    {
//      leds.setPixelColor(i,leds.Color(j+100,180,20));
//      leds.setBrightness(k);
//    }
//    }
//    leds.show();
//    delay(10);
//  }
//

