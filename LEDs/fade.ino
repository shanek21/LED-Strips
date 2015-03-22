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
    checkPower();
    
    //If 'powerOn' is false, break the loop
    if (!powerOn)
    {
      return;
    }
    
    //If up button pressed, increase delay
    checkUp();
    
    //If down button pressed, decrease delay
    checkDown();
    
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
    if (recentPress & refresh%100 == 0)
    {
      recentPress = false;
      Serial.println("Refresh in fade");
    }
  }
}
