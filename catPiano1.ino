const int A = 2; //A goes into digital pin 2
const int B = 3; //B goes into digital pin 3
const int C = 4; //C goes into digital pin 4
const int D = 5; //D goes into digital pin 5
const int E = 6; //E goes into digital pin 6

//variables to hold the digital readings of the switches
int valA; 
int valB;
int valC;
int valD;
int valE;

void setup() {
  Serial.begin(9600); //begin serial communication
}

void loop() {
  valA=digitalRead(A); //read pin 2 to get its digital value
  Serial.print(valA); //print value to the serial monitor
  Serial.print(","); //separate values w/commas for parsing on p5's end

  valB=digitalRead(B); //read pin 3 to get its digital value
  Serial.print(valB); //print value to serial monitor
  Serial.print(","); //separate values w/commas for parsing on p5's end
  
  valC=digitalRead(C); //read pin 4 to get its digital value
  Serial.print(valC); //print value to serial monitor
  Serial.print(","); //separate values w/commas for parsing on p5's end
  
  valD=digitalRead(D); //read pin 5 to get its digital value
  Serial.print(valD); //print value to serial monitor
  Serial.print(","); //separate values w/commas for parsing on p5's end
  
  valE=digitalRead(E); //read pin 6 to get its digital value
  Serial.println(valE); //print value to serial monitor

  delay(1000); //delay one second
  

 

}
