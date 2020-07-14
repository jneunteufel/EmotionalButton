#include <Bounce2.h>  // Including libary for debouncing the button values
#include <Servo.h>    // Including library for the servor motor to create a motion effect

const int JellyPin = 0;      // The number of the Jelly pushbutton pin
const int RndmButtonPin = 1; // The number of random pushbutton pin

int intensityLvl = 0;        // The value to now which intensity the emotion is

const int buzzer = 12;       // Buzzer to arduino pin 12

// Define the pins for the RGB from Arduino Starter Kit
#define RED 9
#define GREEN 10
#define BLUE 11

//Define the button pins
#define buttonPinJelly 0
#define buttonPinRndm 1

// Variables will change if Jelly/Rndm Button is pressed:
int buttonStateJelly = 0;         // variable for reading the pushbutton status Jelly button
int buttonStateRndm = 0;         // variable for reading the pushbutton status Random button

// Instantiate a Bounce object for the Jelly button
Bounce debouncerJelly = Bounce(); 
// Instantiate another Bounce object for the Rndm button
Bounce debouncerRndm = Bounce(); 

// Button status
bool pressedJelly = false;
bool pressedRndm = false;

// Servo motor to create an motion effect
Servo motor;
const int motorPin = 13;      // The Servor motor is connected to pin 13

void setup() {
  // ⚠ Safety stop! -> Ressource: https://github.com/interaction-technologies/Lab01_Haptics by G. Cave
   // Program will not begin unless pin 2 connected to GND
   pinMode(2, INPUT_PULLUP);
   while(digitalRead(2)==HIGH){
      // do nothing!
      delay(500);
   }
   
  // Initialize the LED pin & buzzer as output:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  pinMode(buzzer, OUTPUT);

  motor.attach(motorPin);
   
  // Initialize the pushbutton pin as an input:
  pinMode(buttonPinJelly, INPUT_PULLUP);
  pinMode(buttonPinRndm, INPUT_PULLUP);

  // Ressource: https://github.com/interaction-technologies/Lab01_Haptics/tree/master/Arduino_sketches by G. Cave
  // After setting up the button, setup the Bounce instance :
  debouncerJelly.attach(JellyPin);
  debouncerJelly.interval(5); // interval in ms

   // After setting up the button, setup the Bounce instance :
  debouncerRndm.attach(RndmButtonPin);
  debouncerRndm.interval(5); // interval in ms
}

void loop() {
  // Read the button's pin and right it to variable buttonState_ if pressed
  buttonStateRndm = digitalRead(buttonPinRndm);
  buttonStateJelly = digitalRead(buttonPinJelly);
  
// Update the Bounce instances :
  debouncerJelly.update();
  debouncerRndm.update();

  // Get the updated value :
  int valueJelly = debouncerJelly.read();
  int valueRndm = debouncerRndm.read();

  // Decrease the intesityLvl if the Jelly is pressed and if it is higher than 0 & handle Jelly bool
  if(valueJelly == 0){
    if(intensityLvl > 0 && !pressedJelly)
    {
      intensityLvl -= 1;
    }
    pressedJelly = true;
  }
  else {
    pressedJelly = false;
  }

  // Increase the intesityLvl if the Random is pressed and if it is lower than 4 & handle Rndm bool
  if(valueRndm == 0){
    if(intensityLvl < 4 && !pressedRndm)
    {
      intensityLvl += 1;
    }
    pressedRndm = true;
  }
  else {
    pressedRndm = false;
  }

  // Core Implementation for the different intensity levels
  // The changes will happen to the LED color, the buzzer sound frequency and the servo motor position
  switch(intensityLvl) {
    case 0:
     analogWrite(RED, 255);
     analogWrite(GREEN, 255);
     analogWrite(BLUE, 255);
     noTone(buzzer);
     break;

     case 1:
     analogWrite(RED, 255);
     analogWrite(GREEN, 150);
     analogWrite(BLUE, 0);
     noTone(buzzer);
     break;

     case 2:
     analogWrite(RED, 255);
     analogWrite(GREEN, 50);
     analogWrite(BLUE, 0);
     tone(buzzer, 200);
     break;

     case 3:
     analogWrite(RED, 255);
     analogWrite(GREEN, 10);
     analogWrite(BLUE, 0);
     tone(buzzer, 600);
     break;

     case 4:
     analogWrite(RED, 255);
     analogWrite(GREEN, 0);
     analogWrite(BLUE, 0);
     tone(buzzer, 1000);
     // Move motors to a random position from 10->170 
     uint8_t pos = random(160)+10;
     motor.write(pos);
     break;

     default:
     Serial.print("Upps, something went wrong!\n");
  }
} 
