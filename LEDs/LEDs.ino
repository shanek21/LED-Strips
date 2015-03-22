#include <IRremote.h>

//Create remote values
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

//Set remote button values
bool powerOn = true;
int remoteDelay = 5;
bool recentPress = false;
int refresh = 1;

String currentCode;
String power = "a80e7e5e";
String up = "165412b7";
String down = "5815b090";

//Initialize the RGB pins
int redPin = 9;
int greenPin = 10;
int bluePin = 5;

//Initialize the photo resistor and pot pins
int photoPin = A5;
int potPin = A0;

//Set constants
int time = 100;
int fadeTime = 5;
int lightThreshold = 300;

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
  delay(10);
  checkPower();
  delay(10);
  
  if (!powerOn)
  {
    turnOff();
  }
  else
  {
    rainbow();
  }
  
  //Only reset 'recentPress' every x loops
  refresh++;
  if (recentPress & refresh%100 == 0)
  {
    recentPress = false;
    Serial.println("Refresh in loop");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////FUNCTIONS
//Turn the lights off
void turnOff()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}
