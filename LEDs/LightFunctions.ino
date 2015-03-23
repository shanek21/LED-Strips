////////////////////////////////////
//FUNCTIONS FOR SETTING RGB VALUES//
////////////////////////////////////


//Fade from RGB start to RGB finish
void fade(int start[], int finish[])
{
  startingState = currentState;
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
    //If the IR receiver sees a button press, execute the correct action
    checkButtons();
    
    //If 'powerOn' is false, break the loop
    if (!powerOn | currentState != startingState)
    {
      return;
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
    
    //Reset refresh in x loops
    refresh++;
    if (recentPress & refresh%1000 == 0)
    {
      recentPress = false;
      Serial.println("Refresh in fade");
    }
  }
}


//Taste the rainbow. Fade through the rainbow.
void rainbow()
{
  fade(red, redgreen);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(redgreen, green);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(green, greenblue);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(greenblue, blue);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(blue, bluered);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(bluered, red);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
}

void RBtoGB()
{ 
  fade(bluered, blue);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(blue, greenblue);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(greenblue, blue);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
  
  fade(blue, bluered);
  if (!powerOn | currentState != startingState)
  {
    return;
  }
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
