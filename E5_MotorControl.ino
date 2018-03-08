//E5: Motor Control

const int button = 4; 
boolean buttonState = LOW;  //whether button is HIGH or LOW
int buttonPresses; //number of times the button has been pressed
const int pwmPin = 9;  // 1,2 enable on hbridge
const int motorPinA = 7;
const int motorPinB = 8;
int motorSpeed;
boolean lastButtonState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(pwmPin, OUTPUT);   //arduino pin outputting what the motor should do
  pinMode(motorPinA, OUTPUT); //telling one side of the motor if it should be open or closed
  pinMode(motorPinB, OUTPUT); //telling the other side of the motor if it should be open or closed
}

//from Chapter 2 of Exploring Arduino
boolean debounce(boolean last){ //debouncing the button
  boolean current = digitalRead(button);  //reading the button state
  if(last !=current){   //if last state doesn't equal current
    delay(5); //wait 5 milliseconds
    current = digitalRead(button);  //read the button state again
    }
    return current;   //return the current value of the button
  }
  
void forward(int s) { //code from Katherine's code on github
  digitalWrite(pwmPin, LOW); //first pwm pin is off
  digitalWrite(motorPinA, HIGH); //then open one side of the motor for one direction
  digitalWrite(motorPinB, LOW); //close the other side of motor 
  analogWrite(pwmPin, s); //then pwm pin sends this speed to motor

}

void reverse(int s) {
  digitalWrite(pwmPin, LOW); //first pwm pin is off
  digitalWrite(motorPinA, LOW); //then opposite side of motor is open to reverse direction
  digitalWrite(motorPinB, HIGH); //close other side of motor 
  analogWrite(pwmPin, s); //then run pwm at this speed

}

void brake() {
  digitalWrite(pwmPin, LOW);  //first pwm pin is off
  digitalWrite(motorPinA, LOW); //then both sides of the motor are closed
  digitalWrite(motorPinB, LOW);
  digitalWrite(pwmPin, HIGH); //then run pwm ON and nothing should happen because motor is open

}
void loop() {
  buttonState = debounce(lastButtonState); //using debounce function to debounce
  //Serial.println(buttonState); //print the state of the button in the serial monitor

  if(lastButtonState == LOW && buttonState==HIGH){ //if the button was pressed
      buttonPresses++; //count it as a button press
      motorSpeed = 200; 
      forward(motorSpeed); //turn the motor on in one direction at designated speed
      Serial.println("presses");
Serial.println(buttonPresses);
      
      
      if(lastButtonState == LOW && buttonState==HIGH && buttonPresses==3){ //if the button is pressed 3 times
        motorSpeed = 100;
        reverse(motorSpeed);  //turn the motor in opposite direction at a slower speed
        delay(5000); //keep the motor turning this direction for 5 seconds
        lastButtonState=buttonState;
        }
        
    }
       

  else if(buttonState == LOW){
    //motorSpeed = 0;
    brake();
    }
    //buttonPresses=0;


}



