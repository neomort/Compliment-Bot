// set this to the hardware serial port you wish to use
#define HWSERIAL Serial2
#include <Stepper.h>

const int rightDirPin = 3;
const int rightPWMPin = 4;
const int leftDirPin = 5;
const int leftPWMPin = 6;
 int driveState = 0;

const int stepsPerRevolution = 500;  // change this to fit the number of steps per revolution
const int RevolutionsPerMinute = 60;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 35, 37, 36, 38);

void setup() {
  myStepper.setSpeed(RevolutionsPerMinute);

//  pinMode(button1, INPUT);

  // Motor controller pins
  pinMode(rightDirPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);

  Serial.begin(9600);
  HWSERIAL.begin(9600);

}


void loop() {

  int incomingByte;

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("USB received: ");
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("USB received:");
    HWSERIAL.println(incomingByte, DEC);
  }
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    Serial.print("UART received: ");
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("UART received:");
    HWSERIAL.print(incomingByte, DEC);
    
  }

 

      switch (incomingByte) {
        case 49:
          driveState = 1;
       
        break;
        case 50:
          driveState = 2;
        
        break;
        case 51:
          driveState = 3;
       
        break;
        case 52:
          driveState = 4;
          
        break;
        case 53:
           driveState = 7;
        break;
        case 54:
        driveState = 5;
        break;
         case 55:
         driveState = 6;
         break;
    
      }

         switch (driveState) {
        
      case 2:
        Serial.println("forward" );
        digitalWrite(rightDirPin, 200);
        analogWrite(rightPWMPin, 0);
        digitalWrite(leftDirPin, 200);
        analogWrite(leftPWMPin, 0);
        
        break;
      case 1:
       
        Serial.println("backward");
        digitalWrite(rightDirPin, LOW);
        analogWrite(rightPWMPin, 250);
        digitalWrite(leftDirPin, LOW);
        analogWrite(leftPWMPin, 250);
     
        break;
      case 3:
        Serial.println("turning left");
        digitalWrite(leftDirPin, 0);
        analogWrite(leftPWMPin, 100);
        digitalWrite(rightDirPin, 100);
        analogWrite(rightPWMPin, 0);
  
        break;
      case 4:
        Serial.println("turning right");
        digitalWrite(leftDirPin, 100);
        analogWrite(leftPWMPin, 0);
        digitalWrite(rightDirPin, 0);
        analogWrite(rightPWMPin, 100);
      
        break;
       case 5:
         myStepper.step(stepsPerRevolution);
       break;
       case 6:
         myStepper.step(-stepsPerRevolution);
       break;
        case 7:
//        Serial.println("no info");
        stop();
        digitalWrite(rightDirPin, LOW);
        digitalWrite(rightPWMPin, LOW);
        break;
        }



         }
         


void stop() {

  digitalWrite(rightDirPin, LOW);
  analogWrite(rightPWMPin, 0);
  digitalWrite(leftDirPin, LOW);
  analogWrite(leftPWMPin, 0);

}
