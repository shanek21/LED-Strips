///////////////////
//LED MASTER FILE//
///////////////////

#include <IRremote.h>

//Create remote values
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Set remote variables
bool powerOn = false;
int remoteDelay = 5;
bool recentPress = false;
int refresh = 1;
int remoteRefresh = 0;

int currentState = 1;
String currentCode;
String power = "a80e7e5e";
String up = "165412b7";
String down = "5815b090";
String one = "c9767f76";
String two = "c8155ab1";
String three = "b6996dae";

//Initialize the photo resistor, pot, and RGB pins
int photoPin = A5;
int potPin = A0;
int redPin = 9;
int greenPin = 10;
int bluePin = 5;

//Rainbow!
int red[3] = {255, 0, 0};
int redgreen[3] = {255, 255, 0};
int green[3] = {0, 255, 0};
int greenblue[3] = {0, 255, 255};
int blue[3] = {0, 0, 255};
int bluered[3] = {255, 0, 255};
int white[3] = {255, 255, 255};
int off[3] = {0, 0, 0};

//Initialize state variables
int potValue;
int potTime;
int light;
int currentR;
int currentG;
int currentB;

//Create light states
const int whiteState = 1;
const int RBtoGBState = 2;
const int rainbowState = 3;
int startingState;
//////////////////////////////////////////////////////////////////////////////////////////////////////SETUP
void setup()
{
  //Start the IR receiver
  irrecv.enableIRIn();
  
  //Set the RGB pins as output pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);  
  pinMode(bluePin, OUTPUT);
  
  //Initialize serial and refresh rate
  Serial.begin(9600);
  
  //Turn lights off by default
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
  //Find initial photo resistor and pot values
//  potTime = map(analogRead(potPin), 0, 1025, 0, 1000);
//  light = analogRead(photoPin);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////LOOP
void loop()
{
  checkButtons();
  
  if (!powerOn)
  {
    turnOff();
  }
  else
  {
    switch (currentState)
    {
      case whiteState:
        turnWhite();
        break;
      case RBtoGBState:
        RBtoGB();
        break;
      case rainbowState:
        rainbow();
        break;
    }
  }
}
