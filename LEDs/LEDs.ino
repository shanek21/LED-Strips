////////////////////////
////LED MASTER FILE/////
////////////////////////

#include <IRremote.h>

//Create remote object and sensor pin
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Set initial state of lights
bool powerOn = false;
int currentState = 1;

//Define IR remote button codes
String currentCode;
const String SAFE = "safe";
const String POWER = "a80e7e5e";
String UP = "165412b7";
String DOWN = "5815b090";
String ONE = "c9767f76";
String TWO = "c8155ab1";
String THREE = "b6996dae";
String FOUR = "969ae844";
String REWIND = "e6d07133";
String PLAY = "9a6f0576";
String FASTFORWARD = "9b72c267";
String RECORD = "81a840e6";
String PAUSE = "d049e0a6";
String STOP = "fbad8623";

//Initialize the photo resistor, pot, and RGB pins
int photoPin = A5;
int potPin = A0;
int redPin = 9;
int greenPin = 10;
int bluePin = 5;

//Initialize state variables
int potValue;
int potTime;
int light;
int currentR;
int currentG;
int currentB;
String gameState;
long randNumber;
int patienceReset;
int patience;
int score;
int patienceResetIncrement = 50;
int gameDelay = 5;
int remoteDelay = 5;
int remoteRefresh = 0;

//Define RGB states
int red[3] = {255, 0, 0};
int redgreen[3] = {255, 255, 0};
int green[3] = {0, 255, 0};
int greenblue[3] = {0, 255, 255};
int blue[3] = {0, 0, 255};
int bluered[3] = {255, 0, 255};
int white[3] = {255, 255, 255};
int off[3] = {0, 0, 0};

//Create light states
const int whiteState = 1;
const int RBtoGBState = 2;
const int rainbowState = 3;
const int redState = 4;
const int easterState = 10;
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
}
//////////////////////////////////////////////////////////////////////////////////////////////////////LOOP
void loop()
{
  //Check for IR remote input
  checkButtons();
  
  //Check if lights should be off
  if (!powerOn)
  {
    turnOff();
  }
  
  //Check which state lights should be in
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
      case redState:
        turnRed();
        break;
      case easterState:
        easter();
        currentState = whiteState;
        break;
    }
  }
}
