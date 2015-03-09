//Initialize the RGB pins
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

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

//Initialize state variables
int potValue;
int potTime;
int light;
int currentR;
int currentG;
int currentB;

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
  //Serial.println(light);
  
  int from[] = {0, 0, 0};
  int to[] = {255, 255, 255};
  
  rainbow();
  
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
  
  analogWrite(redPin, startR);
  analogWrite(greenPin, startG);
  analogWrite(bluePin, startB);
  
  int currentR = startR;
  int currentG = startG;
  int currentB = startB;
  
  int finalR = finish[0];
  int finalG = finish[1];
  int finalB = finish[2];
  
  int changeR = (startR - finalR)/255;
  int changeG = (startG - finalG)/255;
  int changeB = (startB - finalB)/255;
  
  for (int x=1; x<256; x++)
  {
    currentR -= changeR;
    currentG -= changeG;
    currentB -= changeB;
    
    analogWrite(redPin, currentR);
    analogWrite(greenPin, currentG);
    analogWrite(bluePin, currentB);
    
    delay(fadeTime);
  }
}

int rainbow()
{
  fade(red, redgreen);
  fade(redgreen, green);
  fade(green, greenblue);
  fade(greenblue, blue);
  fade(blue, bluered);
  fade(bluered, red);
}
