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
  potTime = map(analogRead(potPin), 0, 1025, 0, 1000);
  light = analogRead(photoPin);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////LOOP
void loop()
{
  //If the IR receiver sees a button press, set 'current code' to the button code
  if (irrecv.decode(&results))
  {
    currentCode = String(results.value, HEX);
    //If the code is power, then toggle the power
    if (currentCode == power && !recentPress)
    {
      powerOn = !(powerOn);
      recentPress = true;
      Serial.println(powerOn);
    }
    //Continue looking for button presses
    irrecv.resume();
  }
  
  if (powerOn)
  {
    rainbow();
  }
  else
  {
    turnOff();
  }
  
  delay(100);
  
  //Only reset 'recentPress' every two loops
  refresh++;
  if (refresh%2 == 0)
  {
    recentPress = false;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////FUNCTIONS
//Turn the lights red
void turnRed()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

//Turn the lights green
void turnGreen()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
}

//Turn the lights blue
void turnBlue()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}

//Turn the lights green-blue
void turnGreenBlue()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

//Turn the lights red-blue
void turnRedBlue()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}

//Turn the lights white
void turnWhite()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

//Turn the lights off
void turnOff()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

//Fade from RGB start to RGB finish
void fade(int start[], int finish[])
{
  //Establish the current RGB values
  int startR = start[0];
  int startG = start[1];
  int startB = start[2];
  
  //Establish the desired RGB values
  int finalR = finish[0];
  int finalG = finish[1];
  int finalB = finish[2];
  
  //Set the lights to the current value
  analogWrite(redPin, startR);
  analogWrite(greenPin, startG);
  analogWrite(bluePin, startB);
  
  //Set current value to the start value
  int currentR = startR;
  int currentG = startG;
  int currentB = startB;
  
  //Define an interval to step with
  int changeR = (startR - finalR)/255;
  int changeG = (startG - finalG)/255;
  int changeB = (startB - finalB)/255;
  
  //Step by the interval 255 times
  for (int x=1; x<256; x++)
  {
    //If the IR receiver sees a button press, set 'current code' to the button code
    if (irrecv.decode(&results))
    {
      currentCode = String(results.value, HEX);
      //If power button pressed, toggle power
      if (currentCode == power && !recentPress)
      {
        powerOn = !(powerOn);
        recentPress = true;
        Serial.println("Toggle power!");
        Serial.println(powerOn);
      }
      //If up button pressed, increase delay
      else if (currentCode == up && !recentPress)
      {
        remoteDelay ++;
        recentPress = true;
        Serial.println("Remote delay increased!");
        Serial.println(remoteDelay);
      }
      //If down button pressed, decrease delay
      else if (currentCode == down && !recentPress)
      {
        remoteDelay --;
        recentPress = true;
        Serial.println("Remote delay decreased!");
        Serial.println(remoteDelay);
        if (remoteDelay <= 0)
        {
          remoteDelay = 0;
        }
      }
      
      //If 'powerOn' is false, break the loop
      if (!powerOn)
      {
        break;
      }
      
      //Continue looking for button presses
      irrecv.resume();
    }
    
    //Change the current RGB by the increment
    currentR -= changeR;
    currentG -= changeG;
    currentB -= changeB;
    
    //Publish the current RGB values
    analogWrite(redPin, currentR);
    analogWrite(greenPin, currentG);
    analogWrite(bluePin, currentB);
    
    //Delay and reset 'recentPress'
    delay(remoteDelay);
    recentPress = false;
  }
}

void rainbow()
{
  fade(red, redgreen);
  fade(redgreen, green);
  fade(green, greenblue);
  fade(greenblue, blue);
  fade(blue, bluered);
  fade(bluered, red);
}

void GBtoRB()
{
  if (potTime < 4500)
  {
    if (light < lightThreshold)
    {
      turnGreenBlue();
      potValue = analogRead(potPin);
      potTime = map(potValue, 0, 1025, 10, 5000);
      delay(potTime);
      light = analogRead(photoPin);
    }
    else
    {
      light = analogRead(photoPin);
      turnOff();
      delay(time);
    }
    if (light < lightThreshold)
    {
      turnRedBlue();
      potValue = analogRead(potPin);
      potTime = map(potValue, 0, 1025, 10, 5000);
      //Serial.println(potTime);
      delay(potTime);
      light = analogRead(photoPin);
    }
    else
    {
      light = analogRead(photoPin);
      turnOff();
      delay(time);
    }
  }
  else
  {
    turnWhite();
  }
}
