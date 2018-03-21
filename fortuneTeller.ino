//include lcd and capacitive libraries
#include <LiquidCrystal.h>
#include <CapacitiveSensor.h>

//initialize the lcd object
//LCD pins to Arduino below
//RW pin to 2
//Enable pin to 3
//D4 to 4, D5 to 5, D6 to 6, D7 to 7
LiquidCrystal lcd(2,3,4,5,6,7);

//initialize the capactivite sensor
//sensor byte send pin 8, byte receive pin 12 w/10M ohm resistor on 12 side
CapacitiveSensor sensor = CapacitiveSensor(8,12); 

//an array of arrays below
//asterisk indicates an array of 'pointers'
char* fortunes[]=
{
  "Clear eyes. Full hearts. Can't lose.",  //positive
  "Sashay away!", //negative
  "Make it work!", //positive
  "You've been chopped.", //negative
  "Pack your knives and go.", //negative
  "YAAAAAS QUEEN!", //positive
 };

int i; //variable for random number to be used for pulling a random string from fortunes array

//capacitance variable
int threshold=16000; //when sensor is touched, sensorValue goes above 16000

//starting screen display function so it can keep being called
void success()
{
  lcd.setCursor(1,0); //print on 4th column, first row
  lcd.print("Will your meal");
  lcd.setCursor(2,1); //print on sixth column, second row
  lcd.print("be a success?");
}

void randomFortune()
{
  //use randomSeed to read unused pin to vary randomness
  randomSeed(analogRead(0)); 

  //variable for random pull from array of fortunes
  //should be (0,5) because there are only 6 fortunes but
  //my last phrase was not being selected
  //widening the parameters helped and I have not encountered an error yet
  i=random(0,6); 
  lcd.setCursor(4,0); //set cursor at the 5th column, first row
  lcd.print(fortunes[i]); //print random fortune on lcd

  //for loop and lcd object parameter to have text scroll a certain number
  //of positions towards the left of the screen
  for(int positionCounter = 0; positionCounter<29; positionCounter++)
  {
    lcd.scrollDisplayLeft();
    delay(300); //controls the speed of scrolling
  }

  //Serial.println(fortunes[i]);
  //delay(5000);
  lcd.clear(); //clear the screen
  
}

void setup() 
{
  lcd.begin(16,2); //begin lcd that has 16 columns and 2 rows
  Serial.begin(9600);
  success(); //initialize start screen

}

void loop() 
{
  
  long start = millis(); //long variable because milliseconds will grow quickly, begins when function starts running
  long sensorValue = sensor.capacitiveSensor(30); //read the sensor

  Serial.print(millis() - start); //prints milliseconds from start 
  Serial.print("\t"); //tab
  Serial.println(sensorValue); //prints the value of the sensor
  if(sensorValue>threshold) //if value is above threshold
  {
   lcd.clear();
   randomFortune(); //display random fortune
   lcd.clear(); 
  }
  else //if not
  {
    lcd.clear();
    success(); //display question screen
  }
  


}
