//E5: Motor Control, take 2

const int button = 4; 
boolean buttonState = LOW;  //whether button is HIGH or LOW
int buttonPresses; //number of times the button has been pressed
const int pwmPin = 9;  // 1,2 enable on hbridge
const int motorPinA = 7;
const int motorPinB = 8;
int motorSpeed;
boolean lastButtonState = LOW;

void setup() 
{
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);   //arduino pin outputting what the motor should do
  pinMode(motorPinA, OUTPUT); //telling one side of the motor if it should be open or closed
  pinMode(motorPinB, OUTPUT); //telling the other side of the motor if it should be open or closed
}

//from Chapter 2 of Exploring Arduino
boolean debounce(boolean last)
{ //debouncing the button
  boolean current = digitalRead(button);  //reading the button state
  
  if(last !=current)
  {   //if last state doesn't equal current
    delay(5); //wait 5 milliseconds
    current = digitalRead(button);  //read the button state again
  }
  
  return current;   //return the current value of the button
 }
  
void setMode(int mode)
{
  //forward
   if(mode==1 || mode==2)
  {
      digitalWrite(pwmPin, LOW); //first pwm pin is off
      digitalWrite(motorPinA, HIGH); //then open one side of the motor for one direction
      digitalWrite(motorPinB, LOW); //close the other side of motor 
      analogWrite(pwmPin, 200); //then pwm pin sends this speed to motor
  }
  //reverse
  else if(mode==3)
  {
    digitalWrite(pwmPin, LOW); //first pwm pin is off
    digitalWrite(motorPinA, LOW); //then opposite side of motor is open to reverse direction
    digitalWrite(motorPinB, HIGH); //close other side of motor 
    analogWrite(pwmPin, 100); //then run pwm at this speed

  }
  //OFF/brake (mode=0)
  else
  {
    digitalWrite(pwmPin, LOW);  //first pwm pin is off
    digitalWrite(motorPinA, LOW); //then both sides of the motor are closed
    digitalWrite(motorPinB, LOW);
    digitalWrite(pwmPin, HIGH); //then run pwm ON and nothing should happen because motor is open
  }

}

void loop()
{
  buttonState=debounce(lastButtonState); //read debounced button state
  
  if(lastButtonState==LOW && buttonState==HIGH)
  { //if button is pressed
    buttonPresses++;  //count it as a press and increment the 'mode'
  }
  
  lastButtonState=buttonState; //reset the button value

  if(buttonPresses==4) buttonPresses=0; //if buttonpresses goes through third mode, go back to 0
  
  setMode(buttonPresses); //change the motor's speed and direction
  Serial.println(buttonPresses);
}

  
  
