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
    
    //Set the lights to the current RGB values
    analogWrite(redPin, currentR);
    analogWrite(greenPin, currentG);
    analogWrite(bluePin, currentB);
    
    //Delay by 'remoteDelay'
    delay(remoteDelay);
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


//Turn the lights a shade of red
void turnRedShade(int shade)
{
  analogWrite(redPin, shade);
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


//Turn the lights a shade of green
void turnGreenShade(int shade)
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, shade);
  analogWrite(bluePin, 0);
}


//Turn the lights blue
void turnBlue()
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 255);
}


//Turn the lights a shade of blue
void turnBlueShade(int shade)
{
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, shade);
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


//Hmm... I'm not sure what this does...
void easter()
{
  //Blink 3 times
  turnWhite();
  delay(100);
  turnOff();
  delay(100);
  turnWhite();
  delay(100);
  turnOff();
  delay(100);
  turnWhite();
  delay(1000);
  turnOff();
  delay(100);
  
  Serial.println("EASTER!");
  
  score = 0;
  patienceReset = 1000;
  patience = patienceReset;
  randomFate();
}


//Hmm... I'm not sure what this does...
void randomFate()
{
  Serial.println("Deciding fate");
  randNumber = random(1, 4);
  patience = patienceReset;
  patienceReset -= patienceResetIncrement;
  gameState = SAFE;
  
  if (randNumber == 1)
  {
    redTest();
  }
  else if (randNumber == 2)
  {
    greenTest();
  }
  else if (randNumber == 3)
  {
    blueTest();
  }
}


//Hmm... I'm not sure what this does...
void redTest()
{
  Serial.println("red test");
  turnRed();
  
  while (patience > 0)
  {
    checkButtons();
    if (gameState == "red")
    {
      turnOff();
      score++;
      delay(500);
      randomFate();
      return;
    }
    else if (gameState == "green")
    {
      displayScore();
      return;
    }
    else if (gameState == "blue")
    {
      displayScore();
      return;
    }
    Serial.println(patience);
    patience--;
    turnRedShade(map(patience, 0, patienceReset, 0, 255));
    delay(gameDelay);
  }
  displayScore();
  return;
}


//Hmm... I'm not sure what this does...
void greenTest()
{
  Serial.println("green test");
  turnGreen();
  
  while (patience > 0)
  {
    checkButtons();
    if (gameState == "green")
    {
      turnOff();
      score++;
      delay(500);
      randomFate();
      return;
    }
    else if (gameState == "red")
    {
      displayScore();
      return;
    }
    else if (gameState == "blue")
    {
      displayScore();
      return;
    }
    Serial.println(patience);
    patience--;
    turnGreenShade(map(patience, 0, patienceReset, 0, 255));
    delay(gameDelay);
  }
  displayScore();
  return;
}


//Hmm... I'm not sure what this does...
void blueTest()
{
  Serial.println("blue test");
  turnBlue();
  
  while (patience > 0)
  {
    checkButtons();
    if (gameState == "blue")
    {
      turnOff();
      score++;
      delay(500);
      randomFate();
      return;
    }
    else if (gameState == "green")
    {
      displayScore();
      return;
    }
    else if (gameState == "red")
    {
      displayScore();
      return;
    }
    Serial.println(patience);
    patience--;
    turnBlueShade(map(patience, 0, patienceReset, 0, 255));
    delay(gameDelay);
  }
  displayScore();
  return;
}


void displayScore()
{
  turnWhite();
  delay(1000);
  turnOff();
  delay(100);
  Serial.println("GAME OVER");
  Serial.print("Your score was: ");
  Serial.println(score);
  for (score; score > 0; score--)
  {
    turnWhite();
    delay(100);
    turnOff();
    delay(100);
  }
}
