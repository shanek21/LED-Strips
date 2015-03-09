//Initialize the RGB pins
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

//Initialize the photo resistor and pot pins
int photoPin = A5;
int potPin = A0;

//Set constants
int time = 100;
int lightThreshold = 300;

//Initialize state variables
int potValue;
int potTime;
int light;

void setup()
{
  //Set the RGB pins as output pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);  
  pinMode(bluePin, OUTPUT);
  //pinMode(11, OUTPUT);
  
  //Initialize serial and refresh rate
  Serial.begin(9600);
  
  //Turn lights off by default
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  
  //Find initial photo resistor and pot values
  potTime = map(analogRead(potPin), 0, 1025, 10, 5000);
  light = analogRead(photoPin);
}

void loop()
{
  //Read in photo resistor and pot values
  light = analogRead(photoPin);
  potValue = analogRead(potPin);
  
  //Map pot values from 0-1025 to 10-5000
  potTime = map(potValue, 0, 1025, 10, 5000);

  //Pint the current light value
  Serial.println(light);
  
  fade(
  
//  if (potTime < 4500)
//  {
//    if (light < lightThreshold)
//    {
//      greenBlue();
//      potValue = analogRead(potPin);
//      potTime = map(potValue, 0, 1025, 10, 5000);
//      //Serial.println(potTime);
//      delay(potTime);
//      light = analogRead(photoPin);
//    }
//    else
//    {
//      light = analogRead(photoPin);
//      off();
//      delay(time);
//    }
//    if (light < lightThreshold)
//    {
//      redBlue();
//      potValue = analogRead(potPin);
//      potTime = map(potValue, 0, 1025, 10, 5000);
//      //Serial.println(potTime);
//      delay(potTime);
//      light = analogRead(photoPin);
//    }
//    else
//    {
//      light = analogRead(photoPin);
//      off();
//      delay(time);
//    }
//  }
//  else
//  {
//    white();
//  }
}

//Turn the lights red
void red()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

//Turn the lights green
void green()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0);
}

//Turn the lights blue
void blue()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}

//Turn the lights green-blue
void greenBlue()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

//Turn the lights red-blue
void redBlue()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}

//Turn the lights white
void white()
{
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}

//Turn the lights off
void off()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}

//Fade from RGB start to RGB finish
void fade(start, finish)
{
  //Establish the current RGB values
  currentR = start[0];
  currentG = start[1];
  currentB = start[2];
  
  //Adjust R until start is equal to finish
  if start[0] - finish[0] > 0
  {
    currentR -= 1;
    analogWrite(redPin, currentR);
  }
  else if start[0] - finish[0] < 0
  {
    currentR += 1;
    analogWrite(redPin, currentR);
  }
  
  //Adjust G until start is equal to finish
  if start[1] - finish[1] > 0
  {
    currentG -= 1;
    analogWrite(greenPin, currentG);
  }
  else if start[1] - finish[1] < 0
  {
    currentG += 1;
    analogWrite(greenPin, currentG);
  }
  
  //Adjust B until start is equal to finish
  if start[2] - finish[2] > 0
  {
    currentB -= 1;
    analogWrite(BluePin, currentB);
  }
  else if start[2] - finish[2] < 0
  {
    currentB += 1;
    analogWrite(bluePin, currentB);
  }
}
