//Exploring Touch cap sensor shirt with SD log 
//Interactive Objects and Systems Sp'18
//by Katie Pulles

//include CapSense and SD card libraries
#include <CapacitiveSensor.h>
#include <SD.h>

//include RTC and Wire libraries for real time clock
//part of Adafruit datalogging shield
#include <Wire.h>
#include "RTClib.h"


//variables below are the pins for the SD card chip select and power pins
const int CS_PIN=10;
const int POW_PIN=8;

//define the real time clock object
RTC_PCF8523 RTC;

//initialize strings to hold information for RTC
String year, month, day, hour, minute, second, time, date;

//create four instances of capacitive sensors w/send and receive pins as parameters
CapacitiveSensor sensorA=CapacitiveSensor(2,3); //2 is send pin, 3 is receive
CapacitiveSensor sensorB=CapacitiveSensor(5,4); //5 is send pin, 4 is receive
CapacitiveSensor sensorC=CapacitiveSensor(6,7); //6 is send pin, 7 is receive
CapacitiveSensor sensorD=CapacitiveSensor(8,9); //8 is send pin, 9 is receive

//variable below holds the threshold of the sensors
//int threshold;

void setup() 
{
  //initialize the serial monitor and print text
 Serial.begin(9600);
 Serial.println("Initializing Card");
 //chip select and power pins must be noted as output
 pinMode(CS_PIN, OUTPUT);
 pinMode(POW_PIN, OUTPUT);
 //the SD card needs to draw power from this pin so set it high
 digitalWrite(POW_PIN, HIGH);

//initialize wire and RTC libraries
 Wire.begin();
 RTC.begin();

//if the RTC does not run, print text
//"F" w/in parentheses stores text in parens in flash memory to save microcontroller RAM
 if(!RTC.begin())
 {
  Serial.println(F("RTC is NOT running!"));
 }

//if SD shield does not run, print text
 if(!SD.begin(CS_PIN))
 {
  Serial.println(F("Card Failure"));
  return;
 }
  Serial.println(F("Card Ready"));
}

void loop() 
{
  //variables to hold sensor values
  long capValA = sensorA.capacitiveSensor(30); //read sensor A
  long capValB = sensorB.capacitiveSensor(30); //read sensor B
  long capValC = sensorC.capacitiveSensor(30); //read sensor C
  long capValD = sensorD.capacitiveSensor(30); //read sensor D

//get the current date/time info and store in strings
DateTime datetime=RTC.now();
year = String(datetime.year(), DEC);
month = String(datetime.month(), DEC);
day = String(datetime.day(), DEC);
hour = String(datetime.hour(), DEC);
minute = String(datetime.minute(), DEC);
second = String(datetime.second(), DEC);

//concatenate the strings into date and time
date = year + "\t" + month + "\t" + day;
time = hour + ":" + minute + ":" + second;

//  //time stamp for the RTC in the SD CardLogger shield
//  long timeStamp = millis();

//open a file, name it "log.csv" and write to it
  File dataFile = SD.open("log2.csv", FILE_WRITE);
  if(dataFile)
  {
    dataFile.print(date);
    dataFile.print(",");
    dataFile.print(time);
    dataFile.print(",");
    dataFile.print(capValA); //prints the value of the sensors w/tabs in between
    dataFile.print(",");
    dataFile.print(capValB);
    dataFile.print(",");
    dataFile.print(capValC);
    dataFile.print(",");
    dataFile.println(capValD);
    dataFile.close();

//also print same thing to serial monitor to debug
    Serial.print(date);
    Serial.print("\t");
    Serial.print(time);
    Serial.print("\t");
    Serial.print("\t");
    Serial.print(capValA); //prints the value of the sensors w/tabs in between
    Serial.print("\t");
    Serial.print(capValB);
    Serial.print("\t");
    Serial.print(capValC);
    Serial.print("\t");
    Serial.println(capValD);
  }
  else
  {
    Serial.println("Couldn't open log file"); //if file can't open or be written to
  }
  delay(5000); //wait five seconds between readings
}
